#include <atomic>
#include <chrono>
#include <cstddef>
#include <mutex>
#include <print>
#include <string>
#include <thread>
#include <vector>

// A data race can hide for years: it needs two threads to touch the same
// memory at just the wrong moment, and the program may "work" ten thousand
// times. THREADSANITIZER (TSan) finds races without waiting for the wrong
// moment: it watches every memory access and every lock, and reports two
// accesses that nothing orders, even when this run happened to get away with it.
//
// This program holds four classic concurrency bugs, each with its fix, and
// runs one of them by number:
//
//     rooster          the FIXED versions of all four (clean)
//     rooster 1..4     the BUGGY version of one case
//
// Build with ThreadSanitizer (the CMakeLists.txt does it for you where the
// compiler has it: GCC and Clang on Linux and macOS; MSVC has no ThreadSanitizer).

// ---- 1. A shared counter, unprotected (19.4) ------------------------------------------------
int plain_counter{0};
std::atomic<int> atomic_counter{0};

void count_to_hundred_thousand_plain() {
    for (int i{0}; i < 100'000; ++i) {
        ++plain_counter;
    }
}

void count_to_hundred_thousand_atomic() {
    for (int i{0}; i < 100'000; ++i) {
        ++atomic_counter;
    }
}

// ---- 2. A class that locks in add() and forgets in size() --------------------------------------
// The most common real-world race: most of the class is careful, and one
// accessor is not. Nothing in the language says "this member is protected".
class Readings {
public:
    void add(double celsius) {
        std::lock_guard<std::mutex> lock{mutex_};
        values_.push_back(celsius);
    }

    // BUG: reads values_ while another thread may be inside add().
    std::size_t size_forgetting_the_lock() const {
        return values_.size();
    }

    std::size_t size() const {
        std::lock_guard<std::mutex> lock{mutex_};
        return values_.size();
    }

private:
    mutable std::mutex mutex_;
    std::vector<double> values_;
};

// ---- 3. Two mutexes locked in opposite orders (19.5) ---------------------------------------------
// The two transfers below run one AFTER the other, so this run cannot hang.
// But if they ever overlapped it could deadlock, and TSan reports the
// DANGER ("lock-order-inversion"), not the hang.
struct Account {
    std::mutex mutex;
    int battery{100};
};

void transfer_in_the_order_given(Account& from, Account& to, int amount) {
    std::lock_guard<std::mutex> first{from.mutex};
    std::lock_guard<std::mutex> second{to.mutex};
    from.battery -= amount;
    to.battery += amount;
}

void transfer_safely(Account& from, Account& to, int amount) {
    std::scoped_lock lock{from.mutex, to.mutex};
    from.battery -= amount;
    to.battery += amount;
}

// ---- 4. A plain bool as a stop flag ----------------------------------------------------------------
// Looks harmless: one thread writes it, another polls it. It is still a data
// race (a write and a read, nothing orders them), and the compiler is free
// to read it once and never look again.
bool plain_stop{false};
std::atomic<bool> atomic_stop{false};

int main(int argc, char** argv) {
    int which{argc > 1 ? std::stoi(argv[1]) : 0};

    if (which == 0) {
        std::println("--- 1. atomic counter");
        {
            std::jthread a{count_to_hundred_thousand_atomic};
            std::jthread b{count_to_hundred_thousand_atomic};
        }
        std::println("counter: {}", atomic_counter.load());

        std::println("\n--- 2. every accessor locks");
        Readings readings;
        {
            std::jthread writer{[&readings] {
                for (int i{0}; i < 1'000; ++i) {
                    readings.add(i);
                }
            }};
            std::jthread watcher{[&readings] {
                std::size_t seen{0};
                for (int i{0}; i < 1'000; ++i) {
                    seen = readings.size();
                }
                static_cast<void>(seen);
            }};
        }
        std::println("readings: {}", readings.size());

        std::println("\n--- 3. scoped_lock");
        Account north;
        Account south;
        {
            std::jthread one{[&] { transfer_safely(north, south, 10); }};
        }
        {
            std::jthread two{[&] { transfer_safely(south, north, 20); }};
        }
        std::println("north {}, south {}", north.battery, south.battery);

        std::println("\n--- 4. an atomic stop flag");
        int laps{0};
        {
            std::jthread worker{[&laps] {
                while (!atomic_stop.load()) {
                    ++laps;
                    std::this_thread::sleep_for(std::chrono::milliseconds{1});
                }
            }};
            std::this_thread::sleep_for(std::chrono::milliseconds{20});
            atomic_stop.store(true);
        }
        std::println("the worker ran and stopped: {}", laps > 0);
        return 0;
    }

    std::println("running the BUGGY version of case {}", which);
    switch (which) {
    case 1: {
        std::jthread a{count_to_hundred_thousand_plain};
        std::jthread b{count_to_hundred_thousand_plain};
        break;
    }
    case 2: {
        Readings readings;
        std::jthread writer{[&readings] {
            for (int i{0}; i < 1'000; ++i) {
                readings.add(i);
            }
        }};
        std::jthread watcher{[&readings] {
            std::size_t seen{0};
            for (int i{0}; i < 1'000; ++i) {
                seen = readings.size_forgetting_the_lock();
            }
            static_cast<void>(seen);
        }};
        break;
    }
    case 3: {
        Account north;
        Account south;
        {
            std::jthread one{[&] { transfer_in_the_order_given(north, south, 10); }};
        }
        {
            std::jthread two{[&] { transfer_in_the_order_given(south, north, 20); }};
        }
        std::println("north {}, south {}", north.battery, south.battery);
        break;
    }
    case 4: {
        int laps{0};
        {
            std::jthread worker{[&laps] {
                while (!plain_stop) {
                    ++laps;
                    std::this_thread::sleep_for(std::chrono::milliseconds{1});
                }
            }};
            std::this_thread::sleep_for(std::chrono::milliseconds{20});
            plain_stop = true;
        }
        std::println("the worker ran and stopped: {}", laps > 0);
        break;
    }
    default:
        std::println("no such case");
        return 1;
    }
    return 0;
}
