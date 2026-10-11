#include <coroutine>
#include <cstddef>
#include <new>
#include <print>
#include <string>
#include <utility>

// What does the compiler build when it sees a coroutine? Three things:
//
//   - the FRAME: a block of memory (on the heap) that keeps the coroutine's
//     parameters and local variables alive while it is paused
//   - the PROMISE: an object INSIDE the frame; the coroutine talks to the
//     outside world through it. YOU write its type, and the compiler calls
//     its member functions at fixed moments
//   - the HANDLE: a small pointer-like object, std::coroutine_handle, that
//     the outside world uses to resume() or destroy() the frame
//
//     caller                              heap
//     ------                              ----------------------------
//     StationDay (return object) ----->  | frame                    |
//       holds a coroutine_handle         |   promise (promise_type) |
//                                        |   parameters and locals  |
//                                        |   "where am I paused?"   |
//                                        ----------------------------
//
// This lecture writes the smallest possible coroutine type, and every
// function in it prints a line, so you see the order of events.

struct Noisy {
    std::string name;
    explicit Noisy(std::string n) : name{std::move(n)} { std::println("  {} created", name); }
    ~Noisy() { std::println("  {} destroyed", name); }
};

class StationDay {
public:
    // The compiler looks for exactly this name inside the return type.
    struct promise_type {
        // Called FIRST: allocates the frame. Optional: a class may supply its own
        // operator new (the function a `new` expression calls for raw memory, 9.9),
        // and without one the global version is used. It is here only so you can see it.
        static void* operator new(std::size_t size) {
            std::println("  frame: allocated on the heap");
            return ::operator new(size);
        }
        static void operator delete(void* frame, std::size_t size) {
            std::println("  frame: released");
            ::operator delete(frame, size);
        }

        // Builds the object that the CALLER receives from the coroutine call.
        StationDay get_return_object() {
            std::println("  promise: get_return_object");
            return StationDay{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // Should the coroutine start running at once, or pause before its
        // first line? suspend_always means "pause" (18.6 explains the type).
        std::suspend_always initial_suspend() {
            std::println("  promise: initial_suspend");
            return {};
        }

        // Called when the body is finished. Pausing here (and not at once
        // destroying the frame) lets the owner ask done() and read results.
        std::suspend_always final_suspend() noexcept {
            std::println("  promise: final_suspend");
            return {};
        }

        // Called when the body ends without a value (co_return;).
        void return_void() { std::println("  promise: return_void"); }

        // Called when an exception leaves the body. `throw;` sends it on to
        // whoever called resume().
        void unhandled_exception() { throw; }
    };

    StationDay(StationDay&& other) noexcept
        : handle_{std::exchange(other.handle_, nullptr)} {}
    StationDay(const StationDay&) = delete;
    StationDay& operator=(const StationDay&) = delete;
    StationDay& operator=(StationDay&&) = delete;

    // The owner of the frame must destroy it, exactly once (RAII, 10.6).
    ~StationDay() {
        if (handle_) {
            std::println("  ~StationDay: destroying the frame");
            handle_.destroy();
        }
    }

    void resume() { handle_.resume(); }
    bool done() const { return handle_.done(); }

private:
    explicit StationDay(std::coroutine_handle<promise_type> handle) : handle_{handle} {}

    std::coroutine_handle<promise_type> handle_;
};

// A coroutine: its body contains co_await. `co_await std::suspend_always{}`
// reads "pause here until somebody calls resume()".
StationDay record_day(std::string station) {
    Noisy sensor{"sensor of " + station};
    std::println("  body: start of the day at {}", station);
    co_await std::suspend_always{};
    std::println("  body: noon");
    co_await std::suspend_always{};
    std::println("  body: end of the day");
}

int main() {
    std::println("main: calling the coroutine");
    {
        StationDay day{record_day("north")};
        std::println("main: the call returned; the body has NOT run");

        int resumes{0};
        while (!day.done()) {
            std::println("main: resume number {}", ++resumes);
            day.resume();
            std::println("main: back in main, done() is {}", day.done());
        }
        std::println("main: leaving the block");
    }
    std::println("main: finished");
    return 0;
}
