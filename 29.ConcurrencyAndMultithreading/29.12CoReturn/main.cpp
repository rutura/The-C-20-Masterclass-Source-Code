// co_return ends a coroutine, like a plain return does for a normal
// function - and just like return, a promise_type can support either
// "returns nothing" (return_void) or "returns a value" (return_value), but
// never both. This lecture uses return_void; the commented-out
// return_value below shows the alternative you'd write instead if
// do_work() ended with `co_return someValue;` instead of a bare
// `co_return;`.

#include <print>
#include <coroutine>

struct CoroType {
    struct promise_type {
        int m_value{};

        CoroType get_return_object() { return CoroType(this); }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::rethrow_exception(std::current_exception()); }

        std::suspend_always yield_value(int val) {
            m_value = val;
            return {};
        }

        // The alternative to return_void() below, for a coroutine that
        // ends with `co_return someValue;` instead of a bare `co_return;` -
        // a promise_type may define one or the other, never both.
        /*
        void return_value(int val) {
            std::println("Returning value...");
            m_value = val;
        }
        */

        void return_void() {
            std::println("Returning void...");
        }
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
    std::println("Starting the coroutine...");
    co_yield 1;
    co_yield 2;
    co_yield 3;
    co_return; // triggers return_void() above, then final_suspend()
}

int main() {

    auto task = do_work();

    task.m_handle();
    std::println("value : {}", task.m_handle.promise().m_value);

    std::println("");
    task.m_handle();
    std::println("value : {}", task.m_handle.promise().m_value);
    std::println("coro done : {}", task.m_handle.done());

    std::println("");
    task.m_handle();
    std::println("value : {}", task.m_handle.promise().m_value);
    std::println("coro done : {}", task.m_handle.done());

    std::println("");
    task.m_handle(); // runs the co_return, triggering return_void()
    std::println("value : {}", task.m_handle.promise().m_value);
    std::println("coro done : {}", task.m_handle.done());

    std::println("Done!");

    return 0;
}
