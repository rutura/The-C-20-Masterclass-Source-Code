#include <chrono>
#include <cstddef>
#include <exception>
#include <functional>
#include <numeric>
#include <print>
#include <stdexcept>
#include <stop_token>
#include <thread>
#include <vector>

// A THREAD is an independent line of execution inside your program. All the
// threads of a program share its memory (the heap, the globals), and each has
// its own stack. The operating system decides which ones run, on which core,
// and in which order: from your point of view they run AT THE SAME TIME.
//
// In chapter 18 a coroutine paused at a co_await you wrote. A thread can be
// paused at ANY moment, between any two instructions, and another one runs.
//
// Anything the threads print can come in any order, so those lines start with [varies].

// Adds up readings[first, last) and stores the answer in `result`.
void sum_slice(const std::vector<double>& readings, std::size_t first, std::size_t last, double& result) {
    result = std::accumulate(readings.begin() + static_cast<std::ptrdiff_t>(first),
                             readings.begin() + static_cast<std::ptrdiff_t>(last), 0.0);
}

int main() {
    // ---- 1. Starting a thread ---------------------------------------------------------
    // (If main printed a line here too, the two lines could appear in either
    // order: nothing says which thread gets to its println first.)
    std::println("--- a first thread");
    std::thread hello{[] {
        std::println("hello from the new thread");
    }};

    // join() waits until the thread has finished. A std::thread that is
    // destroyed while it is still joinable (never joined, never detached)
    // calls std::terminate: the library refuses to guess what you wanted.
    hello.join();
    std::println("main: the thread has finished");

    // ---- 2. Arguments and results -----------------------------------------------------
    // The thread constructor COPIES every argument into the new thread (like
    // std::async and bind). A reference parameter would silently bind to the
    // copy, so the compiler refuses unless you say std::ref / std::cref.
    // A thread cannot return a value: it writes into something that outlives it,
    // and the starter reads it AFTER join().
    std::println("\n--- arguments and results");
    std::vector<double> readings(1'000);
    std::iota(readings.begin(), readings.end(), 1.0);

    double first_half{0.0};
    double second_half{0.0};
    std::thread left{sum_slice, std::cref(readings), 0, 500, std::ref(first_half)};
    std::thread right{sum_slice, std::cref(readings), 500, 1'000, std::ref(second_half)};
    left.join();
    right.join();
    std::println("halves: {} + {} = {}", first_half, second_half, first_half + second_half);

    // ---- 3. Many threads, no sharing --------------------------------------------------------
    // Each thread writes only its OWN element of `partial`, and the vector is
    // sized before the threads start. No two threads touch the same memory,
    // so nothing needs protecting (19.4 shows what happens when they do).
    std::println("\n--- four threads");
    constexpr std::size_t thread_count{4};
    std::vector<double> partial(thread_count, 0.0);
    {
        std::vector<std::jthread> team;
        std::size_t slice{readings.size() / thread_count};
        for (std::size_t i{0}; i < thread_count; ++i) {
            team.emplace_back(sum_slice, std::cref(readings), i * slice, (i + 1) * slice, std::ref(partial[i]));
        }
        // std::jthread (C++20) joins in its destructor, so leaving this block
        // waits for all four. That is RAII (10.6) applied to threads.
    }
    for (std::size_t i{0}; i < thread_count; ++i) {
        std::println("thread {} summed {}", i, partial[i]);
    }
    std::println("total: {}", std::accumulate(partial.begin(), partial.end(), 0.0));

    // ---- 4. Asking a thread to stop -----------------------------------------------------------
    // A thread cannot be killed from outside (that would skip its destructors).
    // It is ASKED to stop, and checks. std::jthread has a stop request built
    // in: if the thread function takes a std::stop_token as its FIRST
    // parameter, the jthread passes it in.
    std::println("\n--- a stoppable worker");
    int samples_taken_by_worker{0};
    {
        std::jthread sensor{[&samples_taken_by_worker](std::stop_token token) {
            // Runs when somebody calls request_stop(): on the thread that called it.
            std::stop_callback on_stop{token, [] {
                std::println("[varies] stop requested, the worker will leave its loop");
            }};
            while (!token.stop_requested()) {
                ++samples_taken_by_worker;
                std::this_thread::sleep_for(std::chrono::milliseconds{1});
            }
        }};

        std::this_thread::sleep_for(std::chrono::milliseconds{30});
        sensor.request_stop();
    }
    std::println("the worker took samples before it stopped: {}", samples_taken_by_worker > 0);

    // ---- 5. Errors in a thread ------------------------------------------------------------------
    // An exception that leaves a thread's function calls std::terminate: there
    // is no caller to catch it. The way out is the tool of 18.7:
    // catch inside the thread, keep the std::exception_ptr, and rethrow after join().
    std::println("\n--- an exception from a thread");
    std::exception_ptr failure;
    std::thread fragile{[&failure] {
        try {
            throw std::runtime_error{"the sensor in the thread failed"};
        }
        catch (...) {
            failure = std::current_exception();
        }
    }};
    fragile.join();
    try {
        if (failure) {
            std::rethrow_exception(failure);
        }
    }
    catch (const std::exception& error) {
        std::println("main caught: {}", error.what());
    }

    // Other things you will meet:
    //   std::thread::hardware_concurrency()   how many threads the machine can run at once
    //   std::this_thread::get_id()            the id of the running thread
    //   t.detach()                            let a thread run on its own for ever: almost always a mistake
    return 0;
}
