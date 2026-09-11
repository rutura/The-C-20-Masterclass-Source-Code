#include <print>
#include <array>

int main() {

    // std::array<T, N> - a fixed-size sequence of N values of type T,
    // stored inline (no separate heap allocation). N is part of the type.
    std::array<int, 5> scores{};   // {} zero-initializes every element

    for (std::size_t i{0}; i < scores.size(); ++i) {
        scores[i] = 0;
    }

    std::println("{:>7}{:>10}", "Element", "Value");
    for (std::size_t i{0}; i < scores.size(); ++i) {
        std::println("{:>7}{:>10}", i, scores[i]);
    }

    // .at(i) is the same idea as [i], but it checks the index and throws
    // std::out_of_range instead of silently reading past the array.
    std::println("");
    std::println("{:>7}{:>10}", "Element", "Value");
    for (std::size_t i{0}; i < scores.size(); ++i) {
        std::println("{:>7}{:>10}", i, scores.at(i));
    }

    // Class template argument deduction (CTAD): the element type and N
    // are both inferred from the braced initializer - no <int, 5> needed.
    std::array highScores{32, 27, 64, 18, 95};

    std::print("\nhighScores: ");
    for (std::size_t i{0}; i < highScores.size(); ++i) {
        std::print("{}  ", highScores.at(i));
    }
    std::println("");

    // Range-based for reads more naturally once you don't need the index.
    // A `const int&` element avoids copying (irrelevant for int, habitual
    // for larger element types).
    std::print("highScores (range-based for): ");
    for (const int& score : highScores) {
        std::print("{} ", score);
    }
    std::println("");

    // A non-const reference lets the loop body modify the array in place.
    for (int& score : highScores) {
        score *= 2;
    }

    std::print("highScores (doubled): ");
    for (const int& score : highScores) {
        std::print("{} ", score);
    }
    std::println("");

    // A running total, computed with a range-based for that also declares
    // its own accumulator - the "for (init; cond; range)" form from C++20.
    std::println("\nrunning total:");
    for (int total{0}; const int& score : highScores) {
        total += score;
        std::println("score: {}; running total: {}", score, total);
    }

    // scores.at(10) would throw std::out_of_range here - scores only has
    // 5 elements. Uncomment to see it:
    // scores.at(10);

    return 0;
}
