#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <mutex>
#include <print>
#include <thread>
#include <vector>

// A mutex is the general tool: it protects any amount of code and data. When
// all you need is ONE variable updated safely, there is a cheaper tool: an
// ATOMIC. std::atomic<T> (from <atomic>) is a T whose operations are
// indivisible: no other thread can see, or interleave with, half of one.
//
//     std::atomic<int> counter{0};
//     ++counter;                      one indivisible read-modify-write
//     counter.fetch_add(5);           the same, with a name, returns the OLD value
//     int now{counter.load()};        a safe read
//     counter.store(0);               a safe write

constexpr int station_count{4};
constexpr int readings_per_station{1'000'000};

template <typename Work>
double milliseconds(Work&& work) {
    auto started{std::chrono::steady_clock::now()};
    work();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count();
}

// ---- 1. The counter of 19.4, atomic ------------------------------------------------------
void count_readings(std::atomic<int>& counter) {
    for (int i{0}; i < readings_per_station; ++i) {
        ++counter;
    }
}

// Same, but we do not need the increments ordered against other memory
// operations, only to not be lost: memory_order_relaxed says exactly that.
void count_readings_relaxed(std::atomic<int>& counter) {
    for (int i{0}; i < readings_per_station; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

void count_readings_with_mutex(int& counter, std::mutex& counter_mutex) {
    for (int i{0}; i < readings_per_station; ++i) {
        std::lock_guard<std::mutex> lock{counter_mutex};
        ++counter;
    }
}

// The version of 19.4 that shares nothing, for comparison.
void count_readings_alone(int& my_count) {
    int local{0};
    for (int i{0}; i < readings_per_station; ++i) {
        ++local;
    }
    my_count = local;
}

// ---- 2. Atomics do not have a "maximum" operation: compare_exchange ------------------------
// We want the highest reading of all stations in one shared atomic. "Read it,
// compare, write if bigger" is three steps, and another thread can change the
// value in between. compare_exchange_weak does the last two as ONE step:
//
//     "if the atomic still holds `seen`, replace it with `value` and return true;
//      otherwise load the CURRENT value into `seen` and return false"
//
// so we simply try again. This loop is the standard pattern for any atomic
// update that has no ready-made operation.
void record_peak(std::atomic<int>& peak, int value) {
    int seen{peak.load()};
    while (value > seen && !peak.compare_exchange_weak(seen, value)) {
        // `seen` now holds what another thread wrote; the loop checks again
    }
}

// A reading that is the same on every run, for station `station`.
int reading_of(int station, int index) {
    std::uint32_t state{static_cast<std::uint32_t>(station * 7919 + index) * 2654435761u};
    return static_cast<int>((state >> 16) % 5'000);
}

// ---- 3. Publishing data with an atomic flag ---------------------------------------------------
// One thread prepares a forecast (ordinary variables), then sets a flag. The
// other waits for the flag and reads the forecast. The flag is atomic, and
// the ORDER matters:
//
//     store(true, release)   "everything I wrote before this is visible to
//                             whoever sees this value with an acquire"
//     wait/load(acquire)     "after I see true, I also see all of that"
//
// Without that pairing the reader could see the flag set and still read the old
// forecast, because compilers and processors reorder memory operations.
struct Forecast {
    int hottest{0};
    int coldest{0};
};

int main() {
    const int expected{station_count * readings_per_station};

    std::println("--- an atomic counter");
    std::atomic<int> counter{0};
    double atomic_ms{milliseconds([&] {
        std::vector<std::jthread> stations;
        for (int i{0}; i < station_count; ++i) {
            stations.emplace_back(count_readings, std::ref(counter));
        }
    })};
    std::println("expected {}, got {}", expected, counter.load());

    std::atomic<int> relaxed_counter{0};
    double relaxed_ms{milliseconds([&] {
        std::vector<std::jthread> stations;
        for (int i{0}; i < station_count; ++i) {
            stations.emplace_back(count_readings_relaxed, std::ref(relaxed_counter));
        }
    })};
    std::println("expected {}, got {} (relaxed)", expected, relaxed_counter.load());

    int mutex_counter{0};
    std::mutex counter_mutex;
    double mutex_ms{milliseconds([&] {
        std::vector<std::jthread> stations;
        for (int i{0}; i < station_count; ++i) {
            stations.emplace_back(count_readings_with_mutex, std::ref(mutex_counter), std::ref(counter_mutex));
        }
    })};
    std::vector<int> alone_counts(station_count, 0);
    double alone_ms{milliseconds([&] {
        std::vector<std::jthread> stations;
        for (int i{0}; i < station_count; ++i) {
            stations.emplace_back(count_readings_alone, std::ref(alone_counts[static_cast<std::size_t>(i)]));
        }
    })};
    std::println("[varies] mutex {:.0f} ms, atomic {:.0f} ms, relaxed atomic {:.0f} ms, share nothing {:.0f} ms",
                 mutex_ms, atomic_ms, relaxed_ms, alone_ms);
    std::println("is std::atomic<int> lock free: {}", std::atomic<int>::is_always_lock_free);

    std::println("\n--- the highest reading of all stations");
    std::atomic<int> peak{-1};
    {
        std::vector<std::jthread> stations;
        for (int station{0}; station < station_count; ++station) {
            stations.emplace_back([&peak, station] {
                for (int i{0}; i < 100'000; ++i) {
                    record_peak(peak, reading_of(station, i));
                }
            });
        }
    }
    int serial_peak{-1};
    for (int station{0}; station < station_count; ++station) {
        for (int i{0}; i < 100'000; ++i) {
            serial_peak = std::max(serial_peak, reading_of(station, i));
        }
    }
    std::println("peak {} and the single-threaded answer {}", peak.load(), serial_peak);

    std::println("\n--- publishing with release and acquire");
    Forecast forecast;                                  // ordinary data, no atomics
    std::atomic<bool> ready{false};
    std::jthread reader{[&] {
        ready.wait(false, std::memory_order_acquire);   // sleeps until the value is no longer false
        std::println("reader sees hottest {}, coldest {}", forecast.hottest, forecast.coldest);
    }};
    std::this_thread::sleep_for(std::chrono::milliseconds{20});
    forecast.hottest = 31;
    forecast.coldest = 12;
    ready.store(true, std::memory_order_release);
    ready.notify_one();                                 // wakes a thread blocked in wait()
    reader.join();

    // Limits of atomics:
    //   - they protect ONE variable. "north + south == total" involves three
    //     variables; making each atomic does not make the PAIR consistent.
    //     That needs a mutex.
    //   - "if (count.load() < limit) count.fetch_add(1)" is a race: the check
    //     and the update are two operations. Use compare_exchange.
    //   - the default ordering (memory_order_seq_cst) is the strictest and
    //     the easiest to reason about. Weaker orderings are an optimization
    //     for experts; reach for them only after measuring.
    return 0;
}
