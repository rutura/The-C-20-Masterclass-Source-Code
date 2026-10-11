#include <coroutine>
#include <generator>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "scheduler.h"
#include "task.h"

/*
    Chapter 18 assignment - Coroutines: SOLUTION
*/

// ---- Exercise 1 ----
std::generator<int> hours(int first, int last, int step) {
    for (int hour{first}; hour <= last; hour += step) {
        co_yield hour;
    }
}

// ---- Exercise 2 ----
// Reading number n: 15 + (n * 7) % 11. The sequence never ends, which is
// fine for a generator.
std::generator<double> sensor() {
    for (int n{1};; ++n) {
        co_yield 15.0 + (n * 7) % 11;
    }
}

// ---- Exercise 3 ----
struct Branch {
    int value;
    std::vector<Branch> children;
};

std::generator<int> all_values(const Branch& branch) {
    co_yield branch.value;
    for (const Branch& child : branch.children) {
        co_yield std::ranges::elements_of(all_values(child));
    }
}

// ---- Exercise 4 ----
Task<int> reading(int n) {
    std::println("  reading #{}", n);
    co_return 15 + (n * 7) % 11;
}

Task<double> mean_of_three() {
    int first{co_await reading(1)};
    int second{co_await reading(2)};
    int third{co_await reading(3)};
    co_return (first + second + third) / 3.0;
}

// ---- Exercise 5 ----
Task<int> checked(int n) {
    if (n > 5) {
        throw std::out_of_range{"no such sensor"};
    }
    co_return n * 10;
}

Task<int> safe_checked(int n) {
    try {
        co_return co_await checked(n);
    }
    catch (const std::out_of_range&) {
        co_return -1;
    }
}

// ---- Exercise 6 ----
class Gate {
public:
    struct Awaiter {
        Gate& gate;

        bool await_ready() const noexcept { return gate.open_; }
        void await_suspend(std::coroutine_handle<> handle) const { gate.waiting_.push_back(handle); }
        void await_resume() const noexcept {}
    };

    Awaiter wait() { return Awaiter{*this}; }

    void open() {
        open_ = true;
        // Take the list first: a resumed coroutine could wait again.
        std::vector<std::coroutine_handle<>> to_resume{std::move(waiting_)};
        waiting_.clear();
        for (std::coroutine_handle<> handle : to_resume) {
            handle.resume();
        }
    }

private:
    bool open_{false};
    std::vector<std::coroutine_handle<>> waiting_;
};

Task<void> visitor(Gate& gate, std::string name) {
    std::println("{} waits at the gate", name);
    co_await gate.wait();
    std::println("{} walks through", name);
}

// ---- Exercise 7 ----
Task<void> worker(Scheduler& scheduler, std::string name, int steps) {
    int total{0};
    for (int n{1}; n <= steps; ++n) {
        total += 15 + (n * 7) % 11;
        std::println("{} read #{}", name, n);
        co_await scheduler.yield_now();
    }
    std::println("{} total {}", name, total);
}

// ---- Exercise 8 ----
// The bug was the parameter type: `const std::string& name` is only a
// reference, and the temporary behind it is gone before a lazy Task runs.
Task<void> greet(std::string name) {
    std::println("hello, {}", name);
    co_return;
}

int main() {
    std::println("--- Exercise 1: a generator of hours ---");
    for (int hour : hours(0, 24, 6)) {
        std::print("{} ", hour);
    }
    std::println();

    std::println("\n--- Exercise 2: readings above 20 ---");
    for (double celsius : sensor()
             | std::views::filter([](double value) { return value > 20.0; })
             | std::views::take(5)) {
        std::print("{} ", celsius);
    }
    std::println();

    std::println("\n--- Exercise 3: a tree of values ---");
    Branch tree{1, {
        Branch{2, {Branch{4, {}}, Branch{5, {}}}},
        Branch{3, {Branch{6, {}}}},
    }};
    int sum{0};
    for (int value : all_values(tree)) {
        std::print("{} ", value);
        sum += value;
    }
    std::println("\nsum {}", sum);

    std::println("\n--- Exercise 4: awaiting three readings ---");
    std::println("mean {:.2f}", mean_of_three().get());

    std::println("\n--- Exercise 5: an exception in a task ---");
    std::println("safe_checked(3) = {}", safe_checked(3).get());
    std::println("safe_checked(9) = {}", safe_checked(9).get());
    try {
        checked(9).get();
    }
    catch (const std::out_of_range& error) {
        std::println("caught: {}", error.what());
    }

    std::println("\n--- Exercise 6: a gate ---");
    {
        Gate gate;
        Task<void> north{visitor(gate, "north")};
        Task<void> south{visitor(gate, "south")};
        north.resume();
        south.resume();
        std::println("opening the gate");
        gate.open();
        Task<void> east{visitor(gate, "east")};
        east.resume();
    }

    std::println("\n--- Exercise 7: two workers ---");
    {
        Scheduler scheduler;
        scheduler.spawn(worker(scheduler, "north", 3));
        scheduler.spawn(worker(scheduler, "south", 2));
        scheduler.run();
    }

    std::println("\n--- Exercise 8: fix the lifetime bug ---");
    Task<void> greeting{greet("a station name that is too long to hide inside the string object")};
    greeting.get();

    return 0;
}
