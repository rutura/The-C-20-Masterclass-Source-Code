#include <coroutine>
#include <format>
#include <print>
#include <string>
#include <utility>
#include <vector>

// In 18.4 the coroutine type printed its life story. Here we write one that
// does a real job: a sequence of T values, like std::generator<T> but small
// enough to read in one sitting.
//
// What is new compared to 18.4:
//   - yield_value(): called for every `co_yield`. It saves the value where
//     the iterator can reach it, and pauses
//   - an iterator, so that a range-based for loop (14.2) can drive the
//     coroutine: ++ means "resume", and the end is "the coroutine is done"

template <typename T>
class Generator {
public:
    struct promise_type {
        // Points at the value of the latest co_yield. The value is still
        // alive when we read it: the coroutine is paused INSIDE the
        // co_yield expression, so its operand has not been destroyed yet.
        const T* current{nullptr};

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        // `co_yield x;` becomes `co_await promise.yield_value(x);`
        std::suspend_always yield_value(const T& value) {
            current = &value;
            return {};
        }

        void return_void() {}
        void unhandled_exception() { throw; }
    };

    // The end of the loop is not a position in a container, it is the state
    // "the coroutine finished". A range-based for loop accepts an end marker
    // of ANY type, as long as `iterator == marker` compiles, so a tiny empty
    // struct is enough. (The standard library calls this a sentinel.)
    struct EndMarker {};

    class Iterator {
    public:
        const T& operator*() const { return *handle_.promise().current; }

        Iterator& operator++() {
            handle_.resume();
            return *this;
        }

        bool operator==(EndMarker) const { return handle_.done(); }

    private:
        friend class Generator;
        explicit Iterator(std::coroutine_handle<promise_type> handle) : handle_{handle} {}

        std::coroutine_handle<promise_type> handle_;
    };

    // The coroutine starts paused (initial_suspend), so begin() must run it
    // up to its first co_yield. Calling begin() twice would run it twice:
    // a generator can be walked ONCE.
    Iterator begin() {
        handle_.resume();
        return Iterator{handle_};
    }
    EndMarker end() { return {}; }

    Generator(Generator&& other) noexcept
        : handle_{std::exchange(other.handle_, nullptr)} {}
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator& operator=(Generator&&) = delete;

    ~Generator() {
        if (handle_) {
            handle_.destroy();
        }
    }

private:
    explicit Generator(std::coroutine_handle<promise_type> handle) : handle_{handle} {}

    std::coroutine_handle<promise_type> handle_;
};

// ---- Using it -----------------------------------------------------------------

Generator<int> hours(int first, int last) {
    for (int hour{first}; hour <= last; ++hour) {
        co_yield hour;
    }
}

// The local variables `total` and `count` survive every pause. They live in
// the coroutine's frame (18.4), not on the stack of whoever resumed it.
Generator<double> running_mean(const std::vector<double>& readings) {
    double total{0.0};
    int count{0};
    for (double celsius : readings) {
        total += celsius;
        ++count;
        co_yield total / count;
    }
}

Generator<std::string> labels(const std::vector<double>& readings) {
    int number{1};
    for (double celsius : readings) {
        // A temporary string: it lives until the end of this co_yield
        // expression, which includes the pause, so the iterator can read it.
        co_yield std::format("#{} {:.1f} C", number++, celsius);
    }
}

Generator<long long> fibonacci() {
    long long previous{0};
    long long current{1};
    while (true) {
        co_yield current;
        previous = std::exchange(current, previous + current);
    }
}

int main() {
    std::println("--- hours");
    for (int hour : hours(6, 9)) {
        std::println("{}:00", hour);
    }

    std::vector<double> readings{18.5, 24.0, 21.5, 12.5};

    std::println("\n--- the running mean");
    for (double mean : running_mean(readings)) {
        std::println("{:.2f}", mean);
    }

    std::println("\n--- strings");
    for (const std::string& label : labels(readings)) {
        std::println("{}", label);
    }

    std::println("\n--- an endless one, stopped by the loop");
    for (long long value : fibonacci()) {
        if (value > 100) {
            break;
        }
        std::print("{} ", value);
    }
    std::println();

    // The generator is destroyed at the end of each loop, and its destructor
    // destroys the frame, even for the endless one that never finished. Try
    // removing `handle_.destroy()` and run it under a sanitizer (9.12): the
    // frames are reported as leaked.
    return 0;
}
