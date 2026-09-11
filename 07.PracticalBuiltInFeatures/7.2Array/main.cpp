#include <print>
#include <array>

int main() {

    // std::array<T, N> - a fixed-size sequence of N values of type T,
    // stored inline (no separate heap allocation). N is part of the type.
    //
    // roll_tally counts how many times each face of a six-sided die came
    // up: roll_tally[0] is how many 1s were rolled, roll_tally[1] is how
    // many 2s, and so on - index i holds the count for face (i + 1).
    std::println("tallying six dice rolls:");
    std::array<int, 6> roll_tally{};   // {} zero-initializes every element

    // A fixed sequence of ten rolls, as if a die had already been rolled
    // and someone wrote down the results: 3, 3, 1, 6, 3, 2, 3, 5, 4, 3.
    // Each roll's face value (1..6) becomes the index (face - 1) whose
    // count gets incremented.
    constexpr std::array<int, 10> rolls{3, 3, 1, 6, 3, 2, 3, 5, 4, 3};

    // Tally the rolls into roll_tally: for each roll, its face value
    // (1..6) becomes the index (roll - 1) whose count gets incremented.
    for (std::size_t i{0}; i < rolls.size(); ++i) {
        ++roll_tally[rolls[i] - 1];
    }

    for (std::size_t face{0}; face < roll_tally.size(); ++face) {
        std::println("face {}: {} times", face + 1, roll_tally[face]);
    }

    // .at(face) is the same idea as [face], but it checks the index and
    // throws std::out_of_range instead of silently reading past the array.
    std::println("\nsame tally, read through .at():");
    for (std::size_t face{0}; face < roll_tally.size(); ++face) {
        std::println("face {}: {} times", face + 1, roll_tally.at(face));
    }

    // roll_tally.at(6) would throw std::out_of_range here - a die only has
    // 6 faces, valid indices 0..5. Uncomment to see it:
    // roll_tally.at(6);

    // Class template argument deduction (CTAD): once you know what
    // std::array<T, N> actually means, the compiler can often infer both
    // T and N for you from a braced initializer - no <int, 6> needed.
    std::array lucky_numbers{7, 13, 21, 3, 42, 9};

    // Range-based for reads more naturally once you don't need the index.
    // A `const int&` element avoids copying (irrelevant for int, habitual
    // for larger element types).
    std::print("\nlucky numbers: ");
    for (const int& number : lucky_numbers) {
        std::print("{} ", number);
    }
    std::println("");

    // A non-const reference lets the loop body modify the array in place.
    for (int& number : lucky_numbers) {
        number += 100;
    }

    std::print("shifted by 100: ");
    for (const int& number : lucky_numbers) {
        std::print("{} ", number);
    }
    std::println("");

    // A running total, computed with a range-based for that also declares
    // its own accumulator - the "for (init; cond; range)" form from C++20.
    std::println("\nrunning total:");
    for (int total{0}; const int& number : lucky_numbers) {
        total += number;
        std::println("number: {}, running total: {}", number, total);
    }

    return 0;
}
