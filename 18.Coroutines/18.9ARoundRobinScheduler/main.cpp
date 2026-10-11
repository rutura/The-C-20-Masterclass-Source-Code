#include <print>
#include <stdexcept>
#include <string>

#include "scheduler.h"
#include "task.h"

// 18.7 gave us Task<T>: one result, later. 18.6 showed that an awaiter can
// park the coroutine's handle somewhere and let somebody else resume it.
// Put the two together and you get a SCHEDULER: a queue of paused tasks and
// a loop that resumes them one after the other. No threads involved: it is
// one thread, taking turns.

// A worker that is polite: after every step it lets the others have a turn.
Task<void> worker(Scheduler& scheduler, std::string name, int steps) {
    for (int step{1}; step <= steps; ++step) {
        std::println("{} step {}", name, step);
        co_await scheduler.yield_now();
    }
    std::println("{} is finished", name);
}

// A worker that never yields. It keeps the thread until it ends, because
// nobody can interrupt a coroutine: switching happens only at a co_await.
Task<void> greedy(std::string name, int steps) {
    for (int step{1}; step <= steps; ++step) {
        std::println("{} step {}", name, step);
    }
    co_return;
}

// Tasks can be built from tasks (18.7), and a yield deep inside still lets
// every other task run: yield_now() parks the INNERMOST running coroutine.
Task<int> read_sensor(Scheduler& scheduler, std::string name, int celsius) {
    std::println("  {}: reading started", name);
    co_await scheduler.yield_now();                // pretend the hardware is slow
    std::println("  {}: reading done", name);
    co_return celsius;
}

Task<void> station_report(Scheduler& scheduler, std::string name, int celsius) {
    int first{co_await read_sensor(scheduler, name + " (1)", celsius)};
    int second{co_await read_sensor(scheduler, name + " (2)", celsius + 2)};
    std::println("{} reports {} and {}", name, first, second);
}

Task<void> failing(Scheduler& scheduler) {
    co_await scheduler.yield_now();
    throw std::runtime_error{"the failing task gave up"};
}

int main() {
    std::println("--- three workers take turns");
    {
        Scheduler scheduler;
        scheduler.spawn(worker(scheduler, "north", 3));
        scheduler.spawn(worker(scheduler, "south", 2));
        scheduler.spawn(worker(scheduler, "east", 4));
        scheduler.run();
    }

    std::println("\n--- a worker that never yields");
    {
        Scheduler scheduler;
        scheduler.spawn(worker(scheduler, "north", 2));
        scheduler.spawn(greedy("greedy", 3));
        scheduler.spawn(worker(scheduler, "south", 2));
        scheduler.run();
    }

    std::println("\n--- yielding from inside a task that was awaited");
    {
        Scheduler scheduler;
        scheduler.spawn(station_report(scheduler, "north", 18));
        scheduler.spawn(station_report(scheduler, "south", 25));
        scheduler.run();
    }

    std::println("\n--- an exception waits until the end");
    {
        Scheduler scheduler;
        scheduler.spawn(failing(scheduler));
        scheduler.spawn(worker(scheduler, "north", 2));
        try {
            scheduler.run();
        }
        catch (const std::exception& error) {
            std::println("run() threw: {}", error.what());
        }
    }
    return 0;
}
