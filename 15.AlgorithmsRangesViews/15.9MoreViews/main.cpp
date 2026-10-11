#include <algorithm>
#include <functional>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

// 7.6 introduced iota, filter and transform. A view is a lazy, cheap-to-copy
// description of a sequence; it owns no elements. Here are the rest of the
// views you will actually use, grouped by what they do.
//
// Some need a recent library. All of them are in GCC 15 and 16, current MSVC
// and Clang with libstdc++. Clang with libc++ lacks chunk, slide, stride,
// enumerate, adjacent and cartesian_product so far.

// Prints a label and the elements of a vector (as in 15.4).
template <typename T>
void show(std::string_view label, const std::vector<T>& values) {
    std::print("{:<22}", label);
    for (const T& value : values) {
        std::print(" {}", value);
    }
    std::println();
}

int main() {

    std::vector<int> hours{6, 7, 8, 9, 10, 11, 12, 13};
    std::vector<double> temperatures{11.5, 12.0, 14.5, 17.0, 20.0, 23.5, 24.0, 22.5};

    // A view holds no elements, so there is nothing to print. To LOOK at what a
    // view contains, collect it into a vector: std::ranges::to<std::vector>()
    // at the end of the pipeline does that (15.10 says more about it).
    auto first_three{hours | std::views::take(3) | std::ranges::to<std::vector>()};
    show("take(3):", first_three);

    // --- selecting -----------------------------------------------------------
    std::println("\n--- take, drop, take_while, drop_while, stride, reverse");
    show("drop(5):", hours | std::views::drop(5) | std::ranges::to<std::vector>());
    show("take_while(<9):", hours | std::views::take_while([](int h) { return h < 9; }) | std::ranges::to<std::vector>());
    show("drop_while(<11):", hours | std::views::drop_while([](int h) { return h < 11; }) | std::ranges::to<std::vector>());
    show("stride(3):", hours | std::views::stride(3) | std::ranges::to<std::vector>());
    show("reverse:", hours | std::views::reverse | std::ranges::to<std::vector>());
    show("drop(2) | take(3):", hours | std::views::drop(2) | std::views::take(3) | std::ranges::to<std::vector>());   // views compose

    // An infinite view is fine as long as something stops it.
    show("iota(100) | take(4):", std::views::iota(100) | std::views::take(4) | std::ranges::to<std::vector>());

    // A view can also stand in for an iterator pair. This is the ranges way to
    // sort "just the first three" (15.2 did it with begin() + 3):
    std::vector<double> some{temperatures};
    std::ranges::sort(some | std::views::take(3), std::ranges::greater{});
    show("3 largest first:", some);

    // --- looking inside pairs ---------------------------------------------------
    std::println("\n--- keys and values of a map");
    std::map<std::string, double> latest{{"north", 18.5}, {"south", 24.0}, {"east", 21.5}};
    show("keys:", latest | std::views::keys | std::ranges::to<std::vector>());
    show("values:", latest | std::views::values | std::ranges::to<std::vector>());

    // --- splitting and joining -----------------------------------------------
    std::println("\n--- split, join_with, join");
    std::string line{"north,south,east,west"};
    std::print("split on ',':       ");
    for (auto part : line | std::views::split(',')) {
        std::print(" [{}]", std::string_view{part});                // each part is a subrange of chars
    }
    std::println();

    std::vector<std::string> words{"north", "south", "east"};
    auto joined{words | std::views::join_with(std::string_view{" / "}) | std::ranges::to<std::string>()};
    std::println("join_with ' / ':   {}", joined);

    std::vector<std::vector<int>> days{{1, 2}, {3}, {4, 5, 6}};
    show("join (flatten):", days | std::views::join | std::ranges::to<std::vector>());

    // --- several ranges at once ----------------------------------------------
    std::println("\n--- zip, enumerate, cartesian_product");
    std::print("zip hour:temp:     ");
    for (auto [hour, temperature] : std::views::zip(hours, temperatures) | std::views::take(4)) {
        std::print(" {}h:{}", hour, temperature);
    }
    std::println();

    std::print("enumerate:         ");
    for (auto [index, station] : std::views::enumerate(words)) {
        std::print(" {}={}", index, station);                        // the index comes with the element
    }
    std::println();

    std::print("cartesian_product: ");
    std::vector<char> stations{'N', 'S'};
    std::vector<int> times{6, 12};
    for (auto [station, time] : std::views::cartesian_product(stations, times)) {
        std::print(" {}{}", station, time);                          // every station with every time
    }
    std::println();

    // --- groups and windows -----------------------------------------------------
    std::println("\n--- chunk, slide, adjacent, chunk_by");

    // chunk(n): consecutive, separate groups of n (the last may be shorter).
    std::print("chunk(3):          ");
    for (auto group : hours | std::views::chunk(3)) {
        std::print(" [");
        for (int h : group) {
            std::print("{} ", h);
        }
        std::print("]");
    }
    std::println();

    // slide(n): overlapping windows of n. A moving average! Each window is a
    // view of 3 neighbouring temperatures, and fold_left (15.7) adds them up.
    std::print("3-hour average:    ");
    for (auto window : temperatures | std::views::slide(3)) {
        double average{std::ranges::fold_left(window, 0.0, std::plus<>{}) / 3.0};
        std::print(" {:.2f}", average);
    }
    std::println();

    // adjacent<2> (also called pairwise): every element with its next one.
    std::print("rise per hour:     ");
    for (auto [before, after] : temperatures | std::views::adjacent<2>) {
        std::print(" {:+.1f}", after - before);
    }
    std::println();

    // chunk_by(f): split where f(previous, next) becomes false: runs of consecutive hours here.
    std::vector<int> gaps{6, 7, 8, 12, 13, 18};
    std::print("runs of hours:     ");
    for (auto run : gaps | std::views::chunk_by([](int a, int b) { return b == a + 1; })) {
        std::print(" {}", std::ranges::size(run));
    }
    std::println("   (from 6 7 8 | 12 13 | 18)");
    return 0;
}
