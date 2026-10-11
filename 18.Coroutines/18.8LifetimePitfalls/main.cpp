#include <coroutine>
#include <generator>
#include <print>
#include <span>
#include <string>
#include <vector>

#include "task.h"

// A coroutine outlives the statement that called it. Everything it uses
// after its first pause must still be alive when it comes back, and the
// language does not check that for you. This program has four classic bugs,
// each with its fix, and runs one of them by number:
//
//     rooster          the FIXED versions of all four (safe)
//     rooster 1..4     the BUGGY version of one case
//
// Build with AddressSanitizer (9.12): the CMakeLists.txt does that for you.
// A bug like this often "works" without it, which is the dangerous part.

// A name long enough that the string keeps its characters on the heap and not
// inside the string object itself.
const char* const long_name{"station-with-a-name-too-long-to-fit-inside-the-string-object"};

// ---- 1. A reference parameter bound to a temporary --------------------------------
// The frame stores the REFERENCE, not the string. The call below builds a
// temporary std::string, and it is destroyed at the end of that statement,
// long before the lazy task runs.
Task<void> greet_by_reference(const std::string& name) {
    std::println("hello, {}", name);
    co_return;
}

// Fix: take it BY VALUE. The parameter is copied into the frame (18.4), so it
// lives exactly as long as the coroutine does.
Task<void> greet_by_value(std::string name) {
    std::println("hello, {}", name);
    co_return;
}

// ---- 2. A lambda that is a coroutine and captures --------------------------------
// A lambda's captures live in the closure object, and the coroutine reaches
// them through the closure's address. If the closure dies before the coroutine
// finishes, every use of a capture is a use after free. A temporary closure,
// called at once, dies at the end of the statement.
void lambda_coroutine_bug() {
    std::string name{long_name};
    Task<void> task{[name]() -> Task<void> {
        std::println("hello, {}", name);
        co_return;
    }()};
    task.get();
}

// Fix: pass the data as a PARAMETER of the lambda: parameters are copied into the frame.
void lambda_coroutine_fixed() {
    std::string name{long_name};
    Task<void> task{[](std::string copy) -> Task<void> {
        std::println("hello, {}", copy);
        co_return;
    }(name)};
    task.get();
}

// ---- 3. A generator that outlives what it walks over -----------------------------------
// A std::span (9.8) is a view: a pointer and a size, owning nothing. The span
// parameter is copied into the frame, but the elements it points at are not.
std::generator<int> walk(std::span<const int> values) {
    for (int value : values) {
        co_yield value;
    }
}

// The generator is returned, but `readings` (and its buffer) is destroyed on
// the way out. The span inside the generator now points at freed memory.
std::generator<int> todays_readings_bug() {
    std::vector<int> readings{18, 21, 24, 19, 17, 22, 25, 20};
    return walk(readings);
}

// Fix: give the generator its own copy (a parameter taken by value is stored
// in the frame), or make the vector outlive it.
std::generator<int> walk_copy(std::vector<int> values) {
    for (int value : values) {
        co_yield value;
    }
}

std::generator<int> todays_readings_fixed() {
    std::vector<int> readings{18, 21, 24, 19, 17, 22, 25, 20};
    return walk_copy(readings);
}

// ---- 4. A paused coroutine nobody owns or resumes -----------------------------------
// If a coroutine never finishes and nobody destroys its frame, its local
// variables are never destroyed either: no destructor runs, so every RAII
// object in it (10.6) is silently skipped.
struct Resource {
    Resource() { std::println("  database connection opened"); }
    ~Resource() { std::println("  database connection closed"); }
};

std::coroutine_handle<> parked;

struct Park {
    bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<> handle) const noexcept { parked = handle; }
    void await_resume() const noexcept {}
};

// The coroutine type from 18.6: starts at once, and nobody owns the frame.
struct Job {
    struct promise_type {
        Job get_return_object() { return {}; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { throw; }
    };
};

Job leaked_job() {
    Resource connection;
    co_await Park{};
    std::println("  (never printed)");
}

// Fix: give the frame an OWNER. A Task destroys its frame in its destructor,
// and destroying a paused frame runs the destructors of its live locals.
Task<void> owned_task() {
    Resource connection;
    co_await Park{};
    std::println("  (never printed)");
}

int main(int argc, char** argv) {
    int which{argc > 1 ? std::stoi(argv[1]) : 0};

    if (which == 0) {
        std::println("--- 1. by value");
        Task<void> by_value{greet_by_value(long_name)};
        by_value.get();

        std::println("\n--- 2. a parameter, not a capture");
        lambda_coroutine_fixed();

        std::println("\n--- 3. a generator with its own copy");
        for (int reading : todays_readings_fixed()) {
            std::print("{} ", reading);
        }
        std::println();

        std::println("\n--- 4. an owned coroutine");
        {
            Task<void> owner{owned_task()};
            std::println("  main: starting it");
            // A Task is lazy, so run it to its first pause by hand.
            // (Normally a scheduler does this: 18.9.)
            owner.resume();
            std::println("  main: it is paused; the owner goes out of scope");
        }
        std::println("main: done");
        return 0;
    }

    std::println("running the BUGGY version of case {}", which);
    switch (which) {
    case 1: {
        Task<void> task{greet_by_reference(long_name)};
        task.get();
        break;
    }
    case 2:
        lambda_coroutine_bug();
        break;
    case 3:
        for (int reading : todays_readings_bug()) {
            std::print("{} ", reading);
        }
        std::println();
        break;
    case 4:
        leaked_job();
        std::println("main: the job is paused, and nobody will ever resume it");
        break;
    default:
        std::println("no such case");
        return 1;
    }
    return 0;
}
