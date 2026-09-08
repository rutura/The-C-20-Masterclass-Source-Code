#include <algorithm>
#include <print>
#include <vector>

// A lambda is a function you write inline, right where you need it -
// often to hand to another function. Shape:
//
//   [capture](parameters) { body }
//
// The capture list says which surrounding variables the lambda can see.

int main() {

    // A lambda stored in a variable and called like any function.
    auto add = [](int a, int b) { return a + b; };
    std::println("add(3, 4) = {}", add(3, 4));

    // --- Capture by value: [=] copies the variable into the lambda ---
    int offset{10};
    auto shift_by_value = [=](int n) { return n + offset; };
    offset = 999;                          // the lambda kept the old copy (10)
    std::println("shift_by_value(5) = {}", shift_by_value(5));   // 15

    // --- Capture by reference: [&] refers to the original ---
    int running_total{0};
    auto add_to_total = [&](int n) { running_total += n; };
    add_to_total(3);
    add_to_total(4);
    std::println("running_total = {}", running_total);          // 7

    // --- Passing a lambda where a callable is expected ---
    std::vector<int> nums{5, 2, 8, 1, 9, 3};
    std::sort(nums.begin(), nums.end(),
              [](int a, int b) { return a > b; });              // sort descending
    std::print("sorted: ");
    for (int n : nums) {
        std::print("{} ", n);
    }
    std::println("");

    return 0;
}
