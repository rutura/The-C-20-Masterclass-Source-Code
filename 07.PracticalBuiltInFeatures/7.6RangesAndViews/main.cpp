#include <print>
#include <array>
#include <numeric>
#include <ranges>
#include <string>



int main(){

// The type of a view is far too long to write by hand, so the parameter
// is auto: each call lets the compiler deduce it afresh. auto& and not
// const auto&, since a filter view remembers where its first match is
// and has to be allowed to change while it is iterated.

    auto show_values{
        [](auto& values, const std::string& message) {
            std::print("{}: ", message);
            for (const auto& value : values) {
                std::print("{} ", value);
            }
            std::println("");
        }
    };

    // Named lambdas keep the nested and piped forms below readable: the
    // shape of the expression is the lesson, not the lambda syntax.
    auto is_even{ [](int x) { return x % 2 == 0; } };
    auto square{ [](int x) { return x * x; } };
    auto above_twenty{ [](int x) { return x > 20; } };

    // std::views::iota(a, b) is a view: a lazy, on-demand sequence of
    // integers from a up to (not including) b - nothing is stored.
    auto counted{ std::views::iota(1,11) }; // 1..10
    show_values(counted, "Generate integers 1-10");


    // views::filter is an ordinary callable: hand it a range and a
    // predicate and it returns a view. It does not build a new container,
    // it wraps counted and skips rejected values as they are read.
    auto evens{ std::views::filter(counted,is_even) };
    show_values(evens, "Filtering even integers");
   
    // views::transform is called the same way and lazily maps each value
    // that comes through.
    auto squares(std::views::transform(evens, square));
    show_values(squares, "Mapping even integers to squares");


    // Calls return views, and views are ranges, so a call can be an
    // argument of the next call: no names needed between the steps.
    auto nested{
        std::views::transform(
            std::views::filter(counted,is_even),square
        )
    };
    show_values(nested, "Nested: squares of even integers");


    // Add a third step and the problem shows: the first thing that happens
    // (filter by is_even) is buried in the middle, and the last thing that
    // happens (above_twenty) is the first thing you read.
    auto nested_deeper{
        std::views::filter(
            std::views::transform(
                std::views::filter(counted, is_even),
                square),
            above_twenty) };
    show_values(nested_deeper, "Nested: even squares above 20");


    // The pipe turns the nesting inside out: "range | adaptor(args)" means
    // "adaptor(range, args)". Same views, same values, read left to right.
    auto piped{
        counted | std::views::filter(is_even)
                | std::views::transform(square)
                | std::views::filter(above_twenty) };
    show_values(piped, "Piped: even squares above 20");


    // A view is a range like any other - algorithms such as accumulate
    // work on it directly.
    std::println("Sum of even squares above 20: {}",
        std::accumulate(piped.begin(), piped.end(), 0));


    // The same pipeline works over an existing container, not just a
    // generated sequence.
    constexpr std::array numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto from_array{
        numbers | std::views::filter(is_even)
                | std::views::transform(square) };
    show_values(from_array, "Squares of even integers in numbers");

}