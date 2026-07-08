#include <array>
#include <print>
#include <span>
#include <vector>

// A std::span is a lightweight, non-owning view over a contiguous
// sequence - it doesn't copy the data, just remembers a pointer and a
// size. Unlike the array-parameter functions from the last few lectures
// (which need a separate count parameter, or a fixed size baked into the
// signature), one span-taking function accepts a raw array, a
// std::vector, or a std::array without needing an overload for each.
double sum(std::span<const double> scores) {
    double total{};
    for (auto score : scores) {
        total += score;
    }
    return total;
}

int main() {

    double raw_scores[]{10.5, 34.3, 4.8, 6.5};
    std::vector<double> vector_scores{1.0, 2.0, 3.0, 4.0};
    std::array<double, 3> array_scores{100.0, 200.0, 300.0};

    // The same function, no overloads, no manual size parameter - span
    // deduces its extent from whatever it's constructed from.
    std::println("raw array sum : {}", sum(raw_scores));
    std::println("vector sum : {}", sum(vector_scores));
    std::println("std::array sum : {}", sum(array_scores));

    // A span can also be built explicitly and used to view (and modify) a
    // slice of the underlying data - it doesn't own it, so changes through
    // the span show up in the original container.
    std::span<double> view(vector_scores);
    std::println("");
    std::println("view.size() : {}", view.size());

    view[0] = 999.0;
    std::println("vector_scores[0] after modifying through the span : {}", vector_scores[0]);

    // std::to_array (C++20) builds a std::array from a raw array or a
    // braced list, deducing both the element type and the size - the
    // modern alternative to declaring a raw array and separately tracking
    // its size, or reaching for a non-standard helper.
    auto converted = std::to_array({1, 2, 3, 4, 5});
    std::println("");
    std::println("std::to_array element count : {}", converted.size());

    return 0;
}
