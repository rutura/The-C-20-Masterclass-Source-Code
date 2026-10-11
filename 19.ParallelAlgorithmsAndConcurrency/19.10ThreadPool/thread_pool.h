#pragma once

#include <condition_variable>
#include <cstddef>
#include <deque>
#include <functional>
#include <future>
#include <mutex>
#include <stop_token>
#include <thread>
#include <utility>
#include <vector>

// Starting a thread costs time and memory, and a program that starts one per
// small job (19.3) spends more on starting than on working. A THREAD POOL
// starts a fixed number of worker threads once, and gives them jobs through a
// queue (19.7). Submitting a job returns a std::future (19.8) for its result.
//
//     submit(job) ---> [ job | job | job ] ---> worker 1
//                          the queue      \--> worker 2
//                                          \-> worker 3 ...
class ThreadPool {
public:
    explicit ThreadPool(std::size_t thread_count) {
        for (std::size_t i{0}; i < thread_count; ++i) {
            // A std::jthread passes a stop_token to a function that takes one (19.3).
            workers_.emplace_back([this](std::stop_token token) { work(token); });
        }
    }

    // std::jthread's destructor asks each worker to stop and joins it. The
    // workers finish every job that is still in the queue before they leave,
    // so a job that was submitted always runs.
    ~ThreadPool() = default;

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // `job` is any callable that takes no arguments (capture what it needs in a
    // lambda). The result is a future of whatever the callable returns.
    template <typename F>
    auto submit(F&& job) -> std::future<decltype(job())> {
        using Result = decltype(job());

        // A packaged_task (19.8) runs the callable and puts the result, or the
        // exception it threw, into its future.
        std::packaged_task<Result()> task{std::forward<F>(job)};
        std::future<Result> result{task.get_future()};
        {
            std::lock_guard<std::mutex> lock{mutex_};
            // The queue stores callables of one type: void(). A packaged_task can
            // be moved but not copied, and std::function (15.8) needs copies.
            // std::move_only_function (C++23) is std::function without that demand.
            jobs_.push_back(std::move(task));
        }
        wakeup_.notify_one();
        return result;
    }

    std::size_t size() const { return workers_.size(); }

private:
    void work(std::stop_token token) {
        while (true) {
            std::move_only_function<void()> job;
            {
                std::unique_lock<std::mutex> lock{mutex_};
                // Sleeps until there is a job. If a stop was requested AND the
                // queue is empty, wait() returns false: time to leave.
                if (!wakeup_.wait(lock, token, [this] { return !jobs_.empty(); })) {
                    return;
                }
                job = std::move(jobs_.front());
                jobs_.pop_front();
            }
            job();                                  // run it WITHOUT holding the lock
        }
    }

    mutable std::mutex mutex_;
    std::condition_variable_any wakeup_;
    std::deque<std::move_only_function<void()>> jobs_;
    std::vector<std::jthread> workers_;             // declared last: destroyed (and joined) first
};
