#include <numeric>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

// This is a *taste* of the ranges library, not the full tour - that gets
// its own chapter later. The one idea to take away here: a "view" lets
// you describe a transformation of a sequence without building a new
// container for each step. The work happens as you iterate.

void show(std::string_view label, auto&& range) {
    std::print("{}:", label);
    for (const auto& v : range) {
        std::print(" {}", v);
    }
    std::println("");
}

int main() {
    // std::views::iota generates numbers on demand: 1, 2, 3, ... 10.
    // Nothing is stored - it produces each value as the loop asks for it.
    auto numbers{std::views::iota(1, 11)};
    show("iota(1, 11)", numbers);

    // A view adaptor is applied with the pipe operator |.
    // filter keeps only the elements for which the predicate is true.
    auto evens{numbers | std::views::filter([](int n) { return n % 2 == 0; })};
    show("even only", evens);

    // transform maps each element through a function.
    auto squares{numbers | std::views::transform([](int n) { return n * n; })};
    show("squared", squares);

    // Adaptors chain. This reads left to right: take numbers, keep the
    // evens, square what's left. Still no intermediate container.
    auto even_squares{
        numbers
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * n; })
    };
    show("even, then squared", even_squares);

    // A view works with a real container as its source too.
    std::vector<int> data{3, 1, 4, 1, 5, 9, 2, 6};
    auto big{data | std::views::filter([](int n) { return n >= 4; })};
    show("data >= 4", big);

    // When you finally need a plain number, feed the view to an algorithm.
    int sum{std::accumulate(even_squares.begin(), even_squares.end(), 0)};
    std::println("sum of even squares 1..10: {}", sum);

    return 0;
}
