#include <algorithm>
#include <functional>
#include <numeric>
#include <print>
#include <string_view>
#include <vector>

// Prints a label and the elements of a vector (as in 15.4).
template <typename T>
void show(std::string_view label, const std::vector<T>& values) {
    std::print("{:<26}", label);
    for (const T& value : values) {
        std::print(" {}", value);
    }
    std::println();
}

// <numeric> holds the algorithms that COMBINE values: sums, products, running
// totals, differences. Most of them predate C++20 and have no std::ranges::
// twin, so they take iterator pairs (14.2). The exceptions are iota and the
// C++23 folds.

int main() {

    // Millimetres of rain in each hour of a morning.
    std::vector<int> rain{0, 2, 5, 0, 1, 7, 3, 0};
    show("rain per hour:", rain);

    // accumulate (7.5) folds left to right, in a fixed order.
    // reduce may combine in ANY order, so it needs an operation that gives the
    // same answer in any order (+ does for integers). That freedom is what
    // lets it run in parallel (chapter 19).
    std::println("\n--- accumulate, reduce, fold_left");
    std::println("accumulate: {}", std::accumulate(rain.begin(), rain.end(), 0));
    std::println("reduce:     {}", std::reduce(rain.begin(), rain.end(), 0));
    std::println("fold_left (C++23, takes a range): {}", std::ranges::fold_left(rain, 0, std::plus<>{}));

    // Floating point addition is not exactly associative, so reduce on doubles
    // may differ from accumulate in the last digits. Same rule as 12.7's
    // warning about comparing doubles.

    // Any operation: here, the largest value, written as a fold.
    int largest{std::ranges::fold_left(rain, 0, [](int a, int b) { return std::max(a, b); })};
    std::println("largest, by fold: {}", largest);

    // transform_reduce: transform each element, then reduce the results.
    std::println("\n--- transform_reduce");
    std::vector<double> prices{2.5, 4.0, 1.5};
    std::vector<int> quantities{3, 1, 10};
    double total{std::transform_reduce(prices.begin(), prices.end(), quantities.begin(), 0.0)};
    std::println("dot product (total cost): {}", total);        // 2.5*3 + 4*1 + 1.5*10

    int sum_of_squares{std::transform_reduce(rain.begin(), rain.end(), 0, std::plus<>{}, [](int x) { return x * x; })};
    std::println("sum of squares of rain: {}", sum_of_squares);

    // Counting with a test, as a reduction: transform each value to 0 or 1.
    int wet_hours{std::transform_reduce(rain.begin(), rain.end(), 0, std::plus<>{}, [](int x) { return x > 0 ? 1 : 0; })};
    std::println("hours with any rain: {}", wet_hours);

    // Running totals: a scan keeps every intermediate result.
    std::println("\n--- inclusive_scan, exclusive_scan, partial_sum");
    std::vector<int> running(rain.size());
    std::inclusive_scan(rain.begin(), rain.end(), running.begin());
    show("inclusive_scan:", running);                              // includes the current element

    std::vector<int> before(rain.size());
    std::exclusive_scan(rain.begin(), rain.end(), before.begin(), 0);
    show("exclusive_scan:", before);                               // total BEFORE the current element

    std::vector<int> older(rain.size());
    std::partial_sum(rain.begin(), rain.end(), older.begin());     // the older name of inclusive_scan
    std::println("partial_sum same as inclusive_scan: {}", older == running);

    // The inverse of a scan: what changed from one element to the next.
    std::println("\n--- adjacent_difference");
    std::vector<int> change(rain.size());
    std::adjacent_difference(running.begin(), running.end(), change.begin());
    show("running total -> back:", change);                        // the first element is copied as it is
    std::println("recovered the original: {}", change == rain);

    // Small helpers.
    std::println("\n--- gcd, lcm, midpoint, iota");
    std::println("gcd(12, 18) = {}   lcm(4, 6) = {}   midpoint(10, 20) = {}",
                 std::gcd(12, 18), std::lcm(4, 6), std::midpoint(10, 20));
    std::vector<int> hours(5);
    std::iota(hours.begin(), hours.end(), 6);
    show("iota from 6:", hours);

    // The mean, with the sum and the count as doubles to avoid integer division (5.2).
    double mean{static_cast<double>(std::reduce(rain.begin(), rain.end(), 0)) / static_cast<double>(rain.size())};
    std::println("\naverage rain per hour: {:.3f} mm", mean);
    return 0;
}
