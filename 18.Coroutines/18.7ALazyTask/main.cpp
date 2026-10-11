#include <print>
#include <stdexcept>
#include <string>

#include "task.h"

// The whole Task machinery is in task.h. Read it first (it is explained in
// the notes), then this file shows what it buys us.

Task<int> measure(std::string station, int celsius) {
    std::println("  measuring {}", station);
    co_return celsius;
}

Task<double> average_of_two() {
    std::println("  average: asking the north station");
    int north{co_await measure("north", 18)};
    std::println("  average: asking the south station");
    int south{co_await measure("south", 25)};
    co_return (north + south) / 2.0;
}

Task<int> broken_sensor() {
    std::println("  the sensor is about to fail");
    throw std::runtime_error{"sensor offline"};
    co_return 0;                          // never reached; makes this a coroutine
}

Task<int> careful() {
    try {
        co_return co_await broken_sensor();
    }
    catch (const std::exception& error) {
        std::println("  careful: caught \"{}\" and uses a default", error.what());
        co_return -1;
    }
}

Task<void> announce(std::string text) {
    std::println("  announce: {}", text);
    co_return;
}

Task<int> daily_total() {
    co_await announce("starting the day");
    int total{0};
    total += co_await measure("north", 20);
    total += co_await measure("south", 22);
    co_return total;
}

int main() {
    std::println("--- a task is lazy");
    {
        Task<double> task{average_of_two()};
        std::println("main: the task exists, nothing has run");
        std::println("main: the result is {}", task.get());
    }

    std::println("\n--- a task that is never started");
    {
        Task<int> unused{measure("west", 30)};
        std::println("main: created and thrown away");
    }

    std::println("\n--- tasks awaiting tasks");
    std::println("main: total {}", daily_total().get());

    std::println("\n--- an exception travels up through co_await");
    std::println("main: careful gives {}", careful().get());
    try {
        broken_sensor().get();
    }
    catch (const std::exception& error) {
        std::println("main: caught \"{}\"", error.what());
    }
    return 0;
}
