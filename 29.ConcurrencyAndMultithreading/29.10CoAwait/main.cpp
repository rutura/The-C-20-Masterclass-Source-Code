// A coroutine is a function that can pause partway through and be resumed
// later, picking up right where it left off - a different, lower-level
// mechanism than the threads from earlier in this chapter (a coroutine
// still runs on one thread; it just suspends and resumes on demand rather
// than running continuously). Any function using co_await, co_yield, or
// co_return becomes one - the compiler rewrites it to work this way.
//
// A coroutine needs a return type with a nested promise_type that tells the
// compiler how to handle every point it can pause, resume, finish, or throw.
// This lecture defines the minimum promise_type needed to make co_await work.

#include <print>
#include <coroutine>

struct CoroType {
    struct promise_type {
        CoroType get_return_object() { return CoroType(this); }
        std::suspend_always initial_suspend() { return {}; } // pause immediately, don't run until resumed
        std::suspend_always final_suspend() noexcept { return {}; } // pause once more at the very end
        void unhandled_exception() { std::rethrow_exception(std::current_exception()); }
        void return_void() {}
    };

    explicit CoroType(promise_type* p)
        : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}

    ~CoroType() {
        std::println("Handle destroyed...");
        m_handle.destroy();
    }

    std::coroutine_handle<promise_type> m_handle;
};

CoroType do_work() {
    std::println("Doing first thing...");
    co_await std::suspend_always{}; // pause here until explicitly resumed
    std::println("Doing second thing...");
    co_await std::suspend_always{};
    std::println("Doing third thing...");
}

int main() {

    auto task = do_work();
    // initial_suspend() paused do_work() before it printed anything - it
    // hasn't run yet, just been set up.

    task.m_handle(); // resume: runs until the first co_await, then pauses again
    std::println("coro done : {}", task.m_handle.done());

    task.m_handle.resume(); // resume() and operator() do the same thing
    std::println("coro done : {}", task.m_handle.done());

    task.m_handle.resume();
    std::println("coro done : {}", task.m_handle.done());

    // Resuming again here, after the coroutine has already run to
    // completion, would be undefined behavior - final_suspend() left it
    // paused one last time specifically so the handle stays valid for
    // done() to check, not so it can be resumed again.

    std::println("Done!");

    return 0;
}
