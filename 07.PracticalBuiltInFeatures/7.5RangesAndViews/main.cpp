#include <print>
#include <array>
#include <numeric>
#include <ranges>
#include <string>

int main() {

    // A lambda, since a view's type has no spelling you could write in a
    // parameter list - auto lets each call deduce it fresh.
    auto showValues{
        [](auto& values, const std::string& message) {
            std::print("{}: ", message);
            for (const auto& value : values) {
                std::print("{} ", value);
            }
            std::println("");
        }
    };

    // std::views::iota(a, b) is a view: a lazy, on-demand sequence of
    // integers from a up to (not including) b - nothing is stored.
    auto counted{std::views::iota(1, 11)};   // 1..10
    showValues(counted, "Generate integers 1-10");

    // A view piped through views::filter is still lazy - it does not
    // build a new container, it wraps counted and skips rejected values
    // as they are read.
    auto evens{counted | std::views::filter([](int x) { return x % 2 == 0; })};
    showValues(evens, "Filtering even integers");

    // views::transform lazily maps each value that comes through.
    auto squares{evens | std::views::transform([](int x) { return x * x; })};
    showValues(squares, "Mapping even integers to squares");

    // The pipe (|) reads left to right, like a pipeline: take counted,
    // keep the evens, square what is kept. One expression, no
    // intermediate containers.
    auto evenSquares{
        counted | std::views::filter([](int x) { return x % 2 == 0; })
                | std::views::transform([](int x) { return x * x; })};
    showValues(evenSquares, "Squares of even integers");

    // A view is a range like any other - algorithms such as accumulate
    // work on it directly.
    std::println("Sum of squares of even integers 2-10: {}",
                  std::accumulate(evenSquares.begin(), evenSquares.end(), 0));

    // The same pipeline works over an existing container, not just a
    // generated sequence.
    constexpr std::array numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto fromArray{
        numbers | std::views::filter([](int x) { return x % 2 == 0; })
                | std::views::transform([](int x) { return x * x; })};
    showValues(fromArray, "Squares of even integers in numbers");

    return 0;
}
