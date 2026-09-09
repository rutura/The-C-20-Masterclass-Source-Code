#include <algorithm>
#include <print>
#include <vector>

// A LAMBDA is a small function written inline, right where it is needed
// - usually to hand to another function. Shape:
//
//     [ capture ] ( parameters ) { body }
//
// The capture list says which surrounding variables the lambda may use.

int main() {

    // Stored in a variable, then called like any function.
    auto add = [](int a, int b) { return a + b; };
    std::println("add(3, 4) = {}", add(3, 4));

    // Capture by value: [=] takes a snapshot of `offset` (10).
    int offset{10};
    auto shift = [=](int n) { return n + offset; };
    offset = 999;                              // shift still uses the snapshot
    std::println("shift(5) = {}", shift(5));   // 15

    // Capture by reference: [&] links to the real variable.
    int total{0};
    auto accumulate = [&](int n) { total += n; };
    accumulate(3);
    accumulate(4);
    std::println("total = {}", total);         // 7

    // Passing a lambda where a callable is expected: std::sort takes one
    // to decide ordering.
    std::vector<int> v{5, 2, 8, 1, 9, 3};
    std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });   // descending
    std::print("sorted: ");
    for (int n : v) {
        std::print("{} ", n);
    }
    std::println("");

    return 0;
}
