// The CoroType from the last two lectures only ever produced int values.
// Making it a class template - generator<T> - turns it into a genuinely
// reusable "lazy sequence of T" type, the same pattern C++23's own
// std::generator (not used here, since this lecture builds one from
// scratch to show how it works) is built on.

#include <print>
#include <coroutine>
#include <cassert>

template <typename T>
struct generator {
    struct promise_type {
        T m_value{};

        generator get_return_object() { return generator(this); }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::rethrow_exception(std::current_exception()); }

        std::suspend_always yield_value(T val) {
            m_value = val;
            return {};
        }

        void return_void() {
            std::println("Returning void...");
        }
    };

    explicit generator(promise_type* p)
        : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}

    ~generator() {
        std::println("Handle destroyed...");
        m_handle.destroy();
    }

    // Calling the generator like a function resumes it and hands back
    // whatever it just yielded - a convenient (if simplified) alternative
    // to exposing full begin()/end() iterators, which the next lecture
    // covers with a real third-party generator type.
    T operator()() {
        assert(m_handle != nullptr);
        m_handle.resume();
        return m_handle.promise().m_value;
    }

    std::coroutine_handle<promise_type> m_handle;
};

generator<int> generate_numbers() {
    std::println("generate_numbers starting");
    co_yield 10;
    std::println("After stop point #1");

    co_yield 20;
    std::println("After stop point #2");

    co_yield 30;
    std::println("After stop point #3");
    std::println("generate_numbers ending");
}

generator<int> infinite_number_stream(int start = 0) {
    auto value = start;
    for (int i = 0; ; ++i) {
        co_yield value;
        ++value;
    }
}

generator<int> range(int first, int last) {
    while (first != last) {
        co_yield first++;
    }
}

int main() {

    // generate_numbers() shows the same generator<T> driving a fixed,
    // small sequence with printed checkpoints between each yield -
    // uncomment to see each resume land between those checkpoints.
    /*
    auto task1 = generate_numbers();
    std::println("value : {}", task1());
    std::println("");
    std::println("value : {}", task1());
    std::println("");
    std::println("value : {}", task1());
    std::println("coro done : {}", task1.m_handle.done());
    std::println("");
    task1();
    std::println("coro done : {}", task1.m_handle.done());
    */

    // infinite_number_stream() never returns - a generator can represent a
    // sequence with no fixed end, since each value is only ever produced
    // on demand, one resume at a time. Uncomment cautiously - this loop
    // truly never stops on its own.
    /*
    auto task2 = infinite_number_stream();
    for (std::size_t i{}; ; ++i) {
        std::println("value : {}", task2());
    }
    */

    // range() is the one this lecture actually runs: a finite, bounded
    // sequence, the most common shape a generator takes in practice.
    auto task3 = range(0, 25);
    for (std::size_t i{}; i < 26; ++i) {
        std::println("value[{}] : {}", i, task3());
    }

    std::println("Done!");

    return 0;
}
