#pragma once

#include <coroutine>
#include <exception>
#include <optional>
#include <utility>

// A generator produces many values. A TASK produces ONE result, later: it
// is a function whose work you can describe now and run when you ask for it
// (a LAZY task), and which can wait for other tasks with co_await.
//
//     Task<double> average() {
//         int a{co_await measure("north")};      // runs measure, then comes back here
//         int b{co_await measure("south")};
//         co_return (a + b) / 2.0;               // the result of the whole task
//     }
//
// Three problems to solve in the promise, each with a few lines of code:
//   1. LAZY: initial_suspend pauses, so nothing runs until somebody asks.
//   2. WHO CONTINUES: when a task ends, the coroutine that awaited it must
//      carry on. The task keeps its handle: the CONTINUATION.
//   3. ERRORS: an exception thrown in the task must come out where the
//      result is read, not vanish. We store it and throw it again there.
//
// Number 3 needs a small new tool from <exception>:
//     std::exception_ptr          a handle to an exception object, copyable and storable
//     std::current_exception()    inside a catch block (and in unhandled_exception):
//                                 captures the exception being handled
//     std::rethrow_exception(p)   throws the stored exception, from anywhere

template <typename T>
class Task;

struct PromiseBase {
    std::coroutine_handle<> continuation;      // who awaited this task, if anybody
    std::exception_ptr error;

    std::suspend_always initial_suspend() noexcept { return {}; }

    // When the body ends we do not just stop: we hand control to the
    // continuation. Returning a handle from await_suspend resumes THAT
    // coroutine, as a jump and not as a nested call (symmetric transfer),
    // so a long chain of tasks does not use more and more stack.
    struct FinalAwaiter {
        bool await_ready() const noexcept { return false; }
        template <typename Promise>
        std::coroutine_handle<> await_suspend(std::coroutine_handle<Promise> finished) const noexcept {
            std::coroutine_handle<> next{finished.promise().continuation};
            return next ? next : std::noop_coroutine();       // nobody waits: return to whoever resumed us
        }
        void await_resume() const noexcept {}
    };
    FinalAwaiter final_suspend() noexcept { return {}; }

    void unhandled_exception() { error = std::current_exception(); }

    void rethrow_if_failed() {
        if (error) {
            std::rethrow_exception(error);
        }
    }
};

template <typename T>
struct Promise : PromiseBase {
    std::optional<T> value;

    Task<T> get_return_object();
    void return_value(T result) { value = std::move(result); }

    T result() {
        rethrow_if_failed();
        return std::move(*value);
    }
};

template <>
struct Promise<void> : PromiseBase {
    Task<void> get_return_object();
    void return_void() {}

    void result() { rethrow_if_failed(); }
};

template <typename T>
class Task {
public:
    using promise_type = Promise<T>;
    using Handle = std::coroutine_handle<promise_type>;

    Task(Task&& other) noexcept : handle_{std::exchange(other.handle_, nullptr)} {}
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task& operator=(Task&&) = delete;
    ~Task() {
        if (handle_) {
            handle_.destroy();
        }
    }

    // `co_await some_task` : the AWAITER (18.6) for a task.
    struct Awaiter {
        Handle task;

        bool await_ready() const noexcept { return false; }

        // Remember who is waiting, then START the task by returning its handle.
        std::coroutine_handle<> await_suspend(std::coroutine_handle<> waiting) const noexcept {
            task.promise().continuation = waiting;
            return task;
        }

        // The task is finished: its result (or its exception) is the value of co_await.
        T await_resume() const { return task.promise().result(); }
    };
    Awaiter operator co_await() && noexcept { return Awaiter{handle_}; }

    // For the top of a chain, where no coroutine is awaiting. resume() runs
    // the task until it finishes or pauses on something else, and done() says
    // whether it finished. A scheduler (18.9) is built from handle() and result().
    void resume() { handle_.resume(); }
    bool done() const { return handle_.done(); }
    std::coroutine_handle<> handle() const { return handle_; }

    // The result of a finished task (or its stored exception, thrown here).
    T result() { return handle_.promise().result(); }

    // Run the task to the end and hand over the result. Only for tasks that
    // never wait for anything else than other tasks.
    T get() {
        handle_.resume();
        return result();
    }

private:
    friend struct Promise<T>;
    explicit Task(Handle handle) : handle_{handle} {}

    Handle handle_;
};

template <typename T>
Task<T> Promise<T>::get_return_object() {
    return Task<T>{std::coroutine_handle<Promise<T>>::from_promise(*this)};
}

inline Task<void> Promise<void>::get_return_object() {
    return Task<void>{std::coroutine_handle<Promise<void>>::from_promise(*this)};
}
