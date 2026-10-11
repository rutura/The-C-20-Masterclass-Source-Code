#pragma once

#include <coroutine>
#include <deque>
#include <utility>
#include <vector>

#include "task.h"

// A cooperative, single-threaded scheduler. Tasks take turns: each runs until
// it says `co_await scheduler.yield_now()`, which puts it at the back of the
// line, and then the next one in line gets the thread. Round robin.
//
//     ready_ (front -> back):   [ A ] [ B ] [ C ]
//     run() takes A, resumes it.  A works, then yield_now() puts A at the back:
//                               [ B ] [ C ] [ A ]
//
// Only ONE task runs at any moment, so tasks never need a mutex (chapter 19): they
// can only be interrupted at a co_await they wrote themselves.
class Scheduler {
public:
    // The scheduler takes ownership of the task and queues its first turn.
    void spawn(Task<void> task) {
        ready_.push_back(task.handle());
        tasks_.push_back(std::move(task));
    }

    // Runs until every task has finished. Then, if any task ended with an
    // exception, throws the first one.
    void run() {
        while (!ready_.empty()) {
            std::coroutine_handle<> next{ready_.front()};
            ready_.pop_front();
            next.resume();
        }
        for (Task<void>& task : tasks_) {
            task.result();
        }
    }

    struct YieldAwaiter {
        Scheduler& scheduler;

        bool await_ready() const noexcept { return false; }
        // `waiting` is whatever coroutine is running right now: the innermost
        // one, even when it was reached through several co_await tasks deep.
        void await_suspend(std::coroutine_handle<> waiting) const {
            scheduler.ready_.push_back(waiting);
        }
        void await_resume() const noexcept {}
    };

    YieldAwaiter yield_now() { return YieldAwaiter{*this}; }

private:
    std::deque<std::coroutine_handle<>> ready_;
    std::vector<Task<void>> tasks_;        // keeps every frame alive until the scheduler is gone
};
