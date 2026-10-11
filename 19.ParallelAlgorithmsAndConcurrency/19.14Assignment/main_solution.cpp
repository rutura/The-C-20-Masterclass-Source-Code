#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <execution>
#include <functional>
#include <future>
#include <mutex>
#include <numeric>
#include <print>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "thread_pool.h"

/*
    Chapter 19 assignment - Parallel Algorithms and Concurrency: SOLUTION
*/

// ---- Exercise 3 ----
void count_with_mutex(int& counter, std::mutex& counter_mutex, int readings) {
    for (int i{0}; i < readings; ++i) {
        std::lock_guard<std::mutex> lock{counter_mutex};
        ++counter;
    }
}

void count_with_atomic(std::atomic<int>& counter, int readings) {
    for (int i{0}; i < readings; ++i) {
        ++counter;
    }
}

// ---- Exercise 4 ----
class StationLog {
public:
    void add(std::string note) {
        std::lock_guard<std::mutex> lock{mutex_};
        notes_.push_back(std::move(note));
    }

    std::size_t count() const {
        std::lock_guard<std::mutex> lock{mutex_};
        return notes_.size();
    }

    std::size_t longest() const {
        std::lock_guard<std::mutex> lock{mutex_};
        std::size_t best{0};
        for (const std::string& note : notes_) {
            best = std::max(best, note.size());
        }
        return best;
    }

private:
    mutable std::mutex mutex_;
    std::vector<std::string> notes_;
};

// ---- Exercise 5 ----
struct Account {
    std::mutex mutex;
    int battery{100};
};

void transfer(Account& from, Account& to, int amount) {
    std::scoped_lock lock{from.mutex, to.mutex};
    from.battery -= amount;
    to.battery += amount;
}

// ---- Exercise 6 ----
class Mailbox {
public:
    void put(int value) {
        std::unique_lock<std::mutex> lock{mutex_};
        changed_.wait(lock, [this] { return !full_; });
        value_ = value;
        full_ = true;
        changed_.notify_all();
    }

    int take() {
        std::unique_lock<std::mutex> lock{mutex_};
        changed_.wait(lock, [this] { return full_; });
        full_ = false;
        changed_.notify_all();
        return value_;
    }

private:
    std::mutex mutex_;
    std::condition_variable changed_;
    int value_{0};
    bool full_{false};
};

// ---- Exercise 7 ----
double mean_of(const std::vector<double>& values, std::size_t first, std::size_t last) {
    if (first == last) {
        throw std::invalid_argument{"empty slice"};
    }
    double total{std::accumulate(values.begin() + static_cast<std::ptrdiff_t>(first),
                                 values.begin() + static_cast<std::ptrdiff_t>(last), 0.0)};
    return total / static_cast<double>(last - first);
}

int main() {
    std::println("--- Exercise 1: parallel algorithms ---");
    std::vector<int> celsius(1'000'000);
    for (std::size_t i{0}; i < celsius.size(); ++i) {
        celsius[i] = static_cast<int>(i % 40);
    }
    std::vector<double> fahrenheit(celsius.size());
    std::transform(std::execution::par, celsius.begin(), celsius.end(), fahrenheit.begin(),
                   [](int c) { return c * 9.0 / 5.0 + 32.0; });
    std::println("first five: {} {} {} {} {}", fahrenheit[0], fahrenheit[1], fahrenheit[2], fahrenheit[3], fahrenheit[4]);
    auto hot{std::count_if(std::execution::par, fahrenheit.begin(), fahrenheit.end(), [](double f) { return f > 86.0; })};
    std::println("hotter than 86 F: {}", hot);
    std::vector<long long> numbers(1'000'000);
    std::iota(numbers.begin(), numbers.end(), 1LL);
    std::println("sum: {}", std::reduce(std::execution::par, numbers.begin(), numbers.end(), 0LL));

    std::println("\n--- Exercise 2: four threads, four slices ---");
    std::vector<long long> to_add(2'000);
    std::iota(to_add.begin(), to_add.end(), 1LL);
    std::vector<long long> partial(4, 0);
    {
        std::vector<std::jthread> threads;
        for (std::size_t t{0}; t < 4; ++t) {
            threads.emplace_back([&to_add, &partial, t] {
                auto first{to_add.begin() + static_cast<std::ptrdiff_t>(t * 500)};
                partial[t] = std::accumulate(first, first + 500, 0LL);
            });
        }
    }
    for (std::size_t t{0}; t < partial.size(); ++t) {
        std::println("thread {}: {}", t, partial[t]);
    }
    std::println("total: {}", std::accumulate(partial.begin(), partial.end(), 0LL));

    std::println("\n--- Exercise 3: a shared counter ---");
    int mutex_counter{0};
    std::mutex counter_mutex;
    std::atomic<int> atomic_counter{0};
    {
        std::vector<std::jthread> threads;
        for (int t{0}; t < 4; ++t) {
            threads.emplace_back(count_with_mutex, std::ref(mutex_counter), std::ref(counter_mutex), 250'000);
            threads.emplace_back(count_with_atomic, std::ref(atomic_counter), 250'000);
        }
    }
    std::println("with a mutex: {}", mutex_counter);
    std::println("with an atomic: {}", atomic_counter.load());

    std::println("\n--- Exercise 4: a thread-safe log ---");
    StationLog log;
    {
        std::vector<std::jthread> threads;
        for (int station{0}; station < 4; ++station) {
            threads.emplace_back([&log, station] {
                for (int i{0}; i < 100; ++i) {
                    log.add("station " + std::to_string(station) + " note " + std::to_string(i));
                }
            });
        }
    }
    std::println("{} notes, the longest has {} characters", log.count(), log.longest());

    std::println("\n--- Exercise 5: a ring of transfers ---");
    Account north;
    Account south;
    Account east;
    {
        std::jthread one{[&] {
            for (int i{0}; i < 1'000; ++i) {
                transfer(north, south, 1);
            }
        }};
        std::jthread two{[&] {
            for (int i{0}; i < 1'000; ++i) {
                transfer(south, east, 1);
            }
        }};
        std::jthread three{[&] {
            for (int i{0}; i < 1'000; ++i) {
                transfer(east, north, 1);
            }
        }};
    }
    std::println("north {}, south {}, east {}", north.battery, south.battery, east.battery);
    std::println("total {}", north.battery + south.battery + east.battery);

    std::println("\n--- Exercise 6: a mailbox ---");
    Mailbox mailbox;
    int received_sum{0};
    {
        std::jthread consumer{[&] {
            for (int i{0}; i < 10; ++i) {
                received_sum += mailbox.take();
            }
        }};
        std::jthread producer{[&] {
            for (int value{1}; value <= 10; ++value) {
                mailbox.put(value);
            }
        }};
    }
    std::println("received sum: {}", received_sum);

    std::println("\n--- Exercise 7: futures and an exception ---");
    std::vector<double> readings(1'000);
    std::iota(readings.begin(), readings.end(), 1.0);
    std::vector<std::pair<std::size_t, std::size_t>> slices{{0, 250}, {250, 500}, {500, 500}, {500, 1'000}};
    std::vector<std::future<double>> means;
    for (const auto& [first, last] : slices) {
        means.push_back(std::async(std::launch::async, mean_of, std::cref(readings), first, last));
    }
    for (std::size_t i{0}; i < means.size(); ++i) {
        try {
            std::println("slice {}: mean {}", i, means[i].get());
        }
        catch (const std::exception& error) {
            std::println("slice {}: {}", i, error.what());
        }
    }

    std::println("\n--- Exercise 8: a thread pool ---");
    ThreadPool pool{4};
    std::vector<std::future<long long>> parts;
    for (int part{0}; part < 10; ++part) {
        parts.push_back(pool.submit([part] {
            long long total{0};
            for (long long n{part * 100 + 1}; n <= (part + 1) * 100; ++n) {
                total += n * n;
            }
            return total;
        }));
    }
    long long sum_of_squares{0};
    for (std::future<long long>& part : parts) {
        sum_of_squares += part.get();
    }
    std::println("sum of squares 1..1000: {}", sum_of_squares);

    return 0;
}
