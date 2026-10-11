#include <chrono>
#include <cstddef>
#include <functional>
#include <mutex>
#include <print>
#include <shared_mutex>
#include <thread>
#include <vector>

// 19.4 showed that threads writing the same memory lose updates. A MUTEX
// ("mutual exclusion") fixes it by letting only ONE thread at a time into a
// stretch of code, the CRITICAL SECTION:
//
//     mutex.lock();        if another thread holds it, wait here
//     ++counter;           only one thread at a time gets here
//     mutex.unlock();      let the next one in
//
// Calling lock() and unlock() by hand is the same mistake as new and delete
// (9.9): an early return or an exception skips the unlock, and the mutex stays
// locked for ever. So the mutex is always locked by an object whose destructor
// unlocks it: RAII (10.6) again. std::lock_guard is the simplest one.

constexpr int station_count{4};
constexpr int readings_per_station{1'000'000};

template <typename Work>
double milliseconds(Work&& work) {
    auto started{std::chrono::steady_clock::now()};
    work();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count();
}

// ---- 1. The fixed counter --------------------------------------------------------------
void count_readings(int& counter, std::mutex& counter_mutex) {
    for (int i{0}; i < readings_per_station; ++i) {
        std::lock_guard<std::mutex> lock{counter_mutex};     // locks here, unlocks at the end of each iteration
        ++counter;
    }
}

// ---- 2. A mutex belongs together with the data it protects -------------------------------
// The safest design is a class that owns both, and whose member functions are
// the only way in. Nobody can forget to lock, because nobody can reach the data.
class SharedReadings {
public:
    void add(double celsius) {
        std::lock_guard<std::mutex> lock{mutex_};
        values_.push_back(celsius);
    }

    std::size_t size() const {
        std::lock_guard<std::mutex> lock{mutex_};
        return values_.size();
    }

    double largest() const {
        std::lock_guard<std::mutex> lock{mutex_};
        double best{values_.empty() ? 0.0 : values_.front()};
        for (double value : values_) {
            if (value > best) {
                best = value;
            }
        }
        return best;
    }

private:
    // `mutable` (10.5): locking changes the mutex, not the readings, so a
    // const function like size() is still allowed to lock it.
    mutable std::mutex mutex_;
    std::vector<double> values_;
};

// ---- 3. Deadlock -----------------------------------------------------------------------------
// Two stations share a power budget and move battery between them. A
// transfer needs BOTH mutexes. If thread 1 locks A then B, while thread 2
// locks B then A, each can end up holding one and waiting for the other: they wait for
// ever. That is a DEADLOCK. To be able to show it without hanging the program,
// the mutexes are std::timed_mutex and the waiting is limited to 200 ms.
struct Station {
    std::timed_mutex mutex;
    int battery;
};

constexpr std::chrono::milliseconds patience{200};

// Locks `first`, takes a moment (so the other thread gets to lock ITS first
// mutex), then asks for `second`. Returns false if it gave up.
bool transfer_in_opposite_orders(Station& first, Station& second, int amount) {
    std::unique_lock<std::timed_mutex> first_lock{first.mutex};
    std::this_thread::sleep_for(std::chrono::milliseconds{50});
    std::unique_lock<std::timed_mutex> second_lock{second.mutex, std::defer_lock};
    if (!second_lock.try_lock_for(patience)) {
        // Giving up takes a while (log it, clean up) and the first mutex is
        // still held meanwhile. Without this pause the thread that gives up
        // first would release its mutex, and the OTHER one would get through.
        std::this_thread::sleep_for(patience * 2);
        return false;
    }
    first.battery -= amount;
    second.battery += amount;
    return true;
}

// The cure: take both mutexes in ONE step. std::scoped_lock (C++17) locks any
// number of mutexes with an algorithm that cannot deadlock, whatever the
// order in which you list them.
void transfer_safely(Station& from, Station& to, int amount) {
    std::scoped_lock lock{from.mutex, to.mutex};
    from.battery -= amount;
    to.battery += amount;
}

// ---- 4. Many readers, one writer ------------------------------------------------------------
// A mutex lets in one thread, even if all of them only READ. A
// std::shared_mutex has two modes: any number of readers at once (shared),
// or exactly one writer (exclusive).
class Forecast {
public:
    int hottest() const {
        std::shared_lock<std::shared_mutex> lock{mutex_};     // many threads can be here together
        return hottest_;
    }

    void report(int celsius) {
        std::unique_lock<std::shared_mutex> lock{mutex_};     // exclusive: waits for all readers to leave
        if (celsius > hottest_) {
            hottest_ = celsius;
        }
    }

private:
    mutable std::shared_mutex mutex_;
    int hottest_{-100};
};

int main() {
    const int expected{station_count * readings_per_station};

    std::println("--- a counter protected by a mutex");
    int counter{0};
    std::mutex counter_mutex;
    double locked_ms{milliseconds([&] {
        std::vector<std::jthread> stations;
        for (int i{0}; i < station_count; ++i) {
            stations.emplace_back(count_readings, std::ref(counter), std::ref(counter_mutex));
        }
    })};
    std::println("expected {}, got {}", expected, counter);
    std::println("[varies] took {:.0f} ms (a mutex per increment is slow; 19.6 has a cheaper tool)", locked_ms);

    std::println("\n--- a class that owns its mutex");
    SharedReadings readings;
    {
        std::vector<std::jthread> stations;
        for (int station{0}; station < station_count; ++station) {
            stations.emplace_back([&readings, station] {
                for (int i{0}; i < 1'000; ++i) {
                    readings.add(station * 10.0 + i % 10);
                }
            });
        }
    }
    std::println("{} readings, largest {}", readings.size(), readings.largest());

    std::println("\n--- deadlock");
    Station north{{}, 100};
    Station south{{}, 100};
    bool north_gave_up{false};
    bool south_gave_up{false};
    {
        std::jthread one{[&] { north_gave_up = !transfer_in_opposite_orders(north, south, 10); }};
        std::jthread two{[&] { south_gave_up = !transfer_in_opposite_orders(south, north, 20); }};
    }
    std::println("both threads gave up waiting: {}", north_gave_up && south_gave_up);
    std::println("nothing moved: north {}, south {}", north.battery, south.battery);

    std::println("\n--- the same transfers with scoped_lock");
    {
        std::jthread one{[&] { transfer_safely(north, south, 10); }};
        std::jthread two{[&] { transfer_safely(south, north, 20); }};
    }
    std::println("north {}, south {}", north.battery, south.battery);

    std::println("\n--- readers and a writer");
    Forecast forecast;
    int checks_that_saw_a_value{0};
    std::mutex checks_mutex;
    {
        std::vector<std::jthread> threads;
        for (int reader{0}; reader < 3; ++reader) {
            threads.emplace_back([&] {
                for (int i{0}; i < 1'000; ++i) {
                    if (forecast.hottest() >= -100) {
                        std::lock_guard<std::mutex> lock{checks_mutex};
                        ++checks_that_saw_a_value;
                    }
                }
            });
        }
        threads.emplace_back([&] {
            for (int celsius{15}; celsius <= 30; ++celsius) {
                forecast.report(celsius);
            }
        });
    }
    std::println("hottest reported: {}, checks made: {}", forecast.hottest(), checks_that_saw_a_value);

    // Rules that prevent most trouble:
    //   - keep critical sections SHORT: no sleeping, no waiting for the
    //     network, no printing while holding a lock
    //   - always lock several mutexes with ONE scoped_lock, or in a fixed order everywhere
    //   - never call code you do not control (a callback, a virtual function) while holding a lock
    //   - the data and its mutex belong in one class
    return 0;
}
