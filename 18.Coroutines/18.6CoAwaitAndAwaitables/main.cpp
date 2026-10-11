#include <algorithm>
#include <coroutine>
#include <print>
#include <string>
#include <utility>
#include <vector>

// `co_await thing;` means "pause here until `thing` is ready". What "ready"
// means, and who resumes the coroutine, is decided by `thing`. It is an
// AWAITER: any type with three member functions that the compiler calls:
//
//     bool await_ready()                    Is there anything to wait for? true = no, carry on
//     ... await_suspend(coroutine_handle<>) We are pausing now. Keep the handle, so that someone can resume us
//     T    await_resume()                   We are running again. Whatever this returns is the value of the co_await expression

// ---- A coroutine type nobody owns ---------------------------------------------
// The simplest return type there is: the coroutine starts at once, and
// destroys its own frame when it ends (suspend_never in both places). The
// caller gets nothing back, so nobody can wait for it, ask if it is done, or
// read a result. Fine for the examples of this lecture; 18.7 builds a proper one.
struct Job {
    struct promise_type {
        Job get_return_object() { return {}; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { throw; }
    };
};

// ---- 1. The three questions, asked out loud --------------------------------------
std::coroutine_handle<> parked;      // where the traced coroutine left its handle

struct Traced {
    bool await_ready() const noexcept {
        std::println("  await_ready: nothing to wait for? no");
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle) const noexcept {
        std::println("  await_suspend: pausing, keeping the handle");
        parked = handle;
    }
    int await_resume() const noexcept {
        std::println("  await_resume: running again");
        return 42;
    }
};

Job traced_demo() {
    std::println("  coroutine: before the co_await");
    int answer{co_await Traced{}};
    std::println("  coroutine: the co_await produced {}", answer);
}

// ---- 2. An awaiter that decides at the last moment -------------------------------
// await_suspend can return bool: true = stay paused, false = changed my mind,
// carry on at once. (A third form, returning another handle, is used in 18.7.)
struct Door {
    bool open;

    bool await_ready() const noexcept { return false; }
    bool await_suspend(std::coroutine_handle<> handle) const noexcept {
        if (!open) {
            parked = handle;
        }
        return !open;
    }
    void await_resume() const noexcept {}
};

Job through_door(bool open) {
    std::println("  coroutine: at the door ({})", open ? "open" : "closed");
    co_await Door{open};
    std::println("  coroutine: through the door");
}

// ---- 3. Waiting for time to pass ---------------------------------------------------
// A clock that does not measure anything: somebody calls tick(). A coroutine
// that wants to wait asks the clock for an awaiter, and the clock remembers
// the handle together with the time at which to resume it.
class Clock {
public:
    int now() const { return now_; }

    struct WaitAwaiter {
        Clock& clock;
        int ticks;

        bool await_ready() const noexcept { return ticks <= 0; }
        void await_suspend(std::coroutine_handle<> handle) const {
            clock.waiting_.push_back({clock.now_ + ticks, handle});
        }
        void await_resume() const noexcept {}
    };

    WaitAwaiter wait(int ticks) { return WaitAwaiter{*this, ticks}; }

    void tick() {
        ++now_;
        // Collect first: a resumed coroutine may call wait() again, which
        // adds to waiting_ while we would still be walking it.
        std::vector<std::coroutine_handle<>> due;
        for (const auto& [wake_time, handle] : waiting_) {
            if (wake_time <= now_) {
                due.push_back(handle);
            }
        }
        int current{now_};
        std::erase_if(waiting_, [current](const auto& entry) { return entry.first <= current; });
        for (std::coroutine_handle<> handle : due) {
            handle.resume();
        }
    }

private:
    int now_{0};
    std::vector<std::pair<int, std::coroutine_handle<>>> waiting_;
};

// `station` is taken BY VALUE on purpose: it is copied into the frame (18.4),
// so it is still alive after the caller's string is gone. 18.8 shows what
// happens with a reference.
Job sampler(Clock& clock, std::string station, int every) {
    for (int reading{1}; reading <= 3; ++reading) {
        co_await clock.wait(every);
        std::println("t={}  {} takes reading {}", clock.now(), station, reading);
    }
}

int main() {
    std::println("--- the three questions");
    std::println("main: calling the coroutine");
    traced_demo();
    std::println("main: it is paused; resuming it");
    parked.resume();

    std::println("\n--- deciding in await_suspend");
    through_door(true);
    std::println("main: the open door let it through at once");
    through_door(false);
    std::println("main: the closed door parked it; opening");
    parked.resume();

    std::println("\n--- a clock");
    Clock clock;
    sampler(clock, "north", 2);
    sampler(clock, "south", 3);
    for (int step{0}; step < 9; ++step) {
        clock.tick();
    }

    // The two awaiters from <coroutine> are the simplest possible:
    //     std::suspend_always   await_ready() is false: always pause
    //     std::suspend_never    await_ready() is true:  never pause
    // They are what the earlier lectures used for initial_suspend and
    // final_suspend: "should the coroutine pause here?"
    return 0;
}
