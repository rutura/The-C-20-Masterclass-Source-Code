#include <print>
#include <array>

int main() {

    // std::array<T, N> - a fixed-size sequence of N values of type T,
    // stored inline (no separate heap allocation). N is part of the type.
    std::println("tallying six dice rolls:");
    std::array<int, 6> rollTally{};   // {} zero-initializes every element

    for (std::size_t face{0}; face < rollTally.size(); ++face) {
        rollTally[face] = 0;
    }

    // A roll of the die at index 2 (face value 3) comes up four times.
    rollTally[2] = 4;

    for (std::size_t face{0}; face < rollTally.size(); ++face) {
        std::println("face {}: {} times", face + 1, rollTally[face]);
    }

    // .at(face) is the same idea as [face], but it checks the index and
    // throws std::out_of_range instead of silently reading past the array.
    std::println("\nsame tally, read through .at():");
    for (std::size_t face{0}; face < rollTally.size(); ++face) {
        std::println("face {}: {} times", face + 1, rollTally.at(face));
    }

    // rollTally.at(6) would throw std::out_of_range here - a die only has
    // 6 faces, valid indices 0..5. Uncomment to see it:
    // rollTally.at(6);

    // Class template argument deduction (CTAD): once you know what
    // std::array<T, N> actually means, the compiler can often infer both
    // T and N for you from a braced initializer - no <int, 6> needed.
    std::array luckyNumbers{7, 13, 21, 3, 42, 9};

    // Range-based for reads more naturally once you don't need the index.
    // A `const int&` element avoids copying (irrelevant for int, habitual
    // for larger element types).
    std::print("\nlucky numbers: ");
    for (const int& number : luckyNumbers) {
        std::print("{} ", number);
    }
    std::println("");

    // A non-const reference lets the loop body modify the array in place.
    for (int& number : luckyNumbers) {
        number += 100;
    }

    std::print("shifted by 100: ");
    for (const int& number : luckyNumbers) {
        std::print("{} ", number);
    }
    std::println("");

    // A running total, computed with a range-based for that also declares
    // its own accumulator - the "for (init; cond; range)" form from C++20.
    std::println("\nrunning total:");
    for (int total{0}; const int& number : luckyNumbers) {
        total += number;
        std::println("number: {}, running total: {}", number, total);
    }

    return 0;
}
