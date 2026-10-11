#include <atomic>
#include <chrono>
#include <cstddef>
#include <future>
#include <mutex>
#include <numeric>
#include <print>
#include <set>
#include <stdexcept>
#include <thread>
#include <vector>

#include "thread_pool.h"

// thread_pool.h holds the pool (explained in the notes). This file uses it.

int reading_of(int station) {
    std::this_thread::sleep_for(std::chrono::milliseconds{10});    // a pretend network call
    if (station == 13) {
        throw std::runtime_error{"station 13 does not answer"};
    }
    return 20 + station % 10;
}

int main() {
    // ---- 1. Submit jobs, collect the futures ------------------------------------------------
    std::println("--- jobs and futures");
    ThreadPool pool{4};
    std::println("a pool of {} workers", pool.size());

    std::vector<std::future<int>> futures;
    for (int station{0}; station < 8; ++station) {
        futures.push_back(pool.submit([station] { return reading_of(station); }));
    }
    int total{0};
    for (std::future<int>& future : futures) {
        total += future.get();
    }
    std::println("total of 8 readings: {}", total);

    // ---- 2. Who ran them? ------------------------------------------------------------------------
    std::println("\n--- which threads");
    std::mutex ids_mutex;
    std::set<std::thread::id> ids;
    std::vector<std::future<void>> done;
    for (int i{0}; i < 16; ++i) {
        done.push_back(pool.submit([&] {
            std::this_thread::sleep_for(std::chrono::milliseconds{5});
            std::lock_guard<std::mutex> lock{ids_mutex};
            ids.insert(std::this_thread::get_id());
        }));
    }
    for (std::future<void>& future : done) {
        future.get();
    }
    std::println("16 jobs ran on at most 4 threads: {}", ids.size() <= 4);
    std::println("none of them was the main thread: {}", !ids.contains(std::this_thread::get_id()));

    // ---- 3. Errors travel in the future --------------------------------------------------------------
    std::println("\n--- an exception from a job");
    std::future<int> broken{pool.submit([] { return reading_of(13); })};
    try {
        broken.get();
    }
    catch (const std::exception& error) {
        std::println("the job threw: {}", error.what());
    }
    std::println("the pool still works: {}", pool.submit([] { return reading_of(1); }).get());

    // ---- 4. Splitting one big job into chunks ------------------------------------------------------------
    std::println("\n--- a parallel sum");
    std::vector<int> numbers(1'000'000);
    std::iota(numbers.begin(), numbers.end(), 1);
    constexpr std::size_t chunks{8};
    std::size_t chunk_size{numbers.size() / chunks};
    std::vector<std::future<long long>> partial_sums;
    for (std::size_t c{0}; c < chunks; ++c) {
        partial_sums.push_back(pool.submit([&numbers, c, chunk_size] {
            auto first{numbers.begin() + static_cast<std::ptrdiff_t>(c * chunk_size)};
            return std::accumulate(first, first + static_cast<std::ptrdiff_t>(chunk_size), 0LL);
        }));
    }
    long long sum{0};
    for (std::future<long long>& partial : partial_sums) {
        sum += partial.get();
    }
    std::println("sum {}", sum);

    // ---- 5. Shutting down ------------------------------------------------------------------------------------
    // The destructor stops the workers AFTER they finish the queue.
    std::println("\n--- destroying a pool with jobs still queued");
    std::atomic<int> finished_jobs{0};
    {
        ThreadPool short_lived{2};
        for (int i{0}; i < 20; ++i) {
            short_lived.submit([&finished_jobs] {
                std::this_thread::sleep_for(std::chrono::milliseconds{2});
                ++finished_jobs;
            });
        }
        // no get(): the futures are thrown away. That is fine here, because a
        // future from a packaged_task does NOT wait in its destructor (unlike async, 19.8).
    }
    std::println("jobs that ran before the pool went away: {}", finished_jobs.load());

    return 0;
}
