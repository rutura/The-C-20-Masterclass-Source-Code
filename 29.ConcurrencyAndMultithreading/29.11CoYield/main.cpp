// co_yield produces a value at each pause point instead of just pausing -
// the promise_type stores whatever was yielded so the caller can read it
// off the handle between resumes.

#include <print>
#include <coroutine>

struct CoroType {
    struct promise_type {
        int m_value{};

        CoroType get_return_object() { return CoroType(this); }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::rethrow_exception(std::current_exception()); }

        // yield_value is called for every co_yield in the coroutine body -
        // it stores the yielded value and, like initial/final_suspend,
        // pauses execution right there.
        std::suspend_always yield_value(int val) {
            m_value = val;
            return {};
        }

        // Needed because do_work() below ends with a bare co_return; - a
        // promise_type must supply either return_void (for a coroutine that
        // returns nothing) or return_value (for one that does), never both.
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
    std::println("Starting the coroutine...");
    co_yield 1;
    co_yield 2;
    co_yield 3;
    co_return;
}

int main() {

    auto task = do_work();

    std::println("");
    task.m_handle.resume(); // runs until the first co_yield, pauses, and stores 1
    std::println("value : {}", task.m_handle.promise().m_value);

    std::println("");
    task.m_handle.resume();
    std::println("value : {}", task.m_handle.promise().m_value);

    std::println("");
    task.m_handle.resume();
    std::println("value : {}", task.m_handle.promise().m_value);
    std::println("coro done : {}", task.m_handle.done());

    std::println("------");
    task.m_handle.resume(); // runs the co_return, finishing the coroutine
    std::println("coro done : {}", task.m_handle.done());

    std::println("Done!");

    return 0;
}
