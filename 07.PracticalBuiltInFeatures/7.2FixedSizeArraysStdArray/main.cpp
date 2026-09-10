#include <array>
#include <print>
#include <stdexcept>

// std::array<T, N> is a fixed-size sequence: N values of type T, stored
// back-to-back, size fixed at compile time. It is the modern replacement
// for the C-style `int scores[5];` - same layout, but it knows its own
// size and has real member functions.

int main() {
    // Brace-init every element. The type is spelled out here: 5 ints.
    std::array<int, 5> scores{42, 17, 91, 8, 63};

    // Class template argument deduction (CTAD): the compiler reads the
    // braces and deduces std::array<double, 4> for you.
    std::array temperatures{19.5, 21.0, 18.75, 22.25};

    // size() - how many elements. Always available, unlike a raw array
    // where you had to remember N yourself or use sizeof tricks.
    std::println("scores has {} elements", scores.size());
    std::println("temperatures has {} elements", temperatures.size());

    // Two ways to reach an element:
    //   []    - fast, no checking; an out-of-range index is undefined behavior
    //   at()  - checks the index and throws std::out_of_range if it is bad
    std::println("scores[0]    : {}", scores[0]);
    std::println("scores.at(4) : {}", scores.at(4));

    // front() / back() - first and last element without doing the index math.
    std::println("first: {}, last: {}", scores.front(), scores.back());

    // Range-based for. `const int&` when only reading: no copy, cannot
    // change the element by accident.
    std::print("all scores:");
    for (const int& s : scores) {
        std::print(" {}", s);
    }
    std::println("");

    // `int&` when you mean to modify the element in place.
    for (int& s : scores) {
        s += 10;
    }
    std::print("after +10 :");
    for (const int& s : scores) {
        std::print(" {}", s);
    }
    std::println("");

    // fill() sets every element to the same value.
    std::array<int, 5> cleared{};
    cleared.fill(-1);
    std::println("cleared.back() after fill(-1): {}", cleared.back());

    // Range-for with an init-statement (C++20): the running total lives
    // only for the loop, not the whole function.
    for (int total{0}; const int& s : scores) {
        total += s;
        std::println("saw {}, running total {}", s, total);
    }

    // at() is the one that protects you. [] would just wander off the end.
    try {
        std::println("scores.at(99): {}", scores.at(99));
    } catch (const std::out_of_range& ex) {
        std::println("caught out_of_range: {}", ex.what());
    }

    return 0;
}
