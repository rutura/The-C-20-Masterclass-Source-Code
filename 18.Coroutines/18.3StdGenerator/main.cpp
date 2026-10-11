#include <generator>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>

// std::generator<T> (C++23) is a coroutine's return type that stands for a
// SEQUENCE of T values, produced one at a time, only when somebody asks.

// ---- 1. An endless sequence ------------------------------------------------
// Nothing can hold an endless list of readings. A generator can, because it
// produces the next one on demand and never "has" the rest.
std::generator<double> sensor() {
    unsigned state{12345};
    while (true) {
        // A simple pseudo-random step, so the numbers are the same on every machine.
        state = state * 1103515245u + 12345u;
        double fraction{static_cast<double>((state >> 16) % 1000) / 1000.0};
        co_yield 10.0 + 20.0 * fraction;
    }
}

// ---- 2. A generator can yield references -----------------------------------
// generator<std::string> would copy every name. With `const std::string&` the
// caller reads the string where it already lives. The coroutine is paused
// while the caller looks at it, so the string cannot go away in between.
struct Node {
    std::string name;
    std::vector<Node> children;
};

std::generator<const std::string&> names(const Node& node) {
    co_yield node.name;
    for (const Node& child : node.children) {
        // A generator can hand out everything another generator produces.
        co_yield std::ranges::elements_of(names(child));
    }
}

// ---- 3. Cleanup runs even when the caller stops early ----------------------
struct Link {
    Link() { std::println("  [link] opened"); }
    ~Link() { std::println("  [link] closed"); }
};

std::generator<int> hourly() {
    Link link;
    for (int hour{0}; hour < 24; ++hour) {
        co_yield hour;
    }
}

// ---- 4. Exceptions come out at the caller ------------------------------------
std::generator<int> flaky(int working) {
    for (int reading{1};; ++reading) {
        if (reading > working) {
            throw std::runtime_error{"the sensor stopped answering"};
        }
        co_yield reading * 10;
    }
}

int main() {

    std::println("--- an endless sensor, three readings");
    int shown{0};
    for (double celsius : sensor()) {
        std::println("{:.1f}", celsius);
        if (++shown == 3) {
            break;
        }
    }

    // A generator is a RANGE (chapter 15): it has begin() and end(), so the
    // views and algorithms work on it. They are lazy too, so even a pipeline
    // over an endless sequence is fine as long as something ends it.
    std::println("\n--- as a range: the first four readings above 25");
    auto hot{sensor()
        | std::views::filter([](double celsius) { return celsius > 25.0; })
        | std::views::take(4)};
    for (double celsius : hot) {
        std::println("{:.1f}", celsius);
    }

    std::println("\n--- collected into a vector");
    auto mild{sensor()
        | std::views::take(6)
        | std::views::transform([](double celsius) { return celsius - 10.0; })
        | std::ranges::to<std::vector>()};
    std::println("{} values, first {:.1f}, last {:.1f}", mild.size(), mild.front(), mild.back());

    std::println("\n--- a recursive generator: the station network");
    Node network{"network", {
        Node{"north", {Node{"hill", {}}, Node{"valley", {}}}},
        Node{"south", {Node{"coast", {}}}},
    }};
    for (const std::string& name : names(network)) {
        std::println("{}", name);
    }

    std::println("\n--- stopping early");
    for (int hour : hourly()) {
        std::println("hour {}", hour);
        if (hour == 2) {
            break;
        }
    }
    std::println("after the loop");

    std::println("\n--- an exception inside the generator");
    try {
        for (int value : flaky(2)) {
            std::println("value {}", value);
        }
    }
    catch (const std::exception& error) {
        std::println("caught: {}", error.what());
    }

    // Two rules to remember:
    //   - a generator is single-pass: you can walk it once, from the start.
    //     Calling begin() a second time is not allowed.
    //   - it is move-only, like a unique_ptr (9.10): it owns the paused function.
    return 0;
}
