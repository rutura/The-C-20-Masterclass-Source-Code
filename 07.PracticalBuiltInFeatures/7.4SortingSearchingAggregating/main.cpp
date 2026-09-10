#include <algorithm>
#include <array>
#include <numeric>
#include <print>
#include <string>
#include <vector>

// Once data is in a container, the library already has the common
// operations on it: sort it, search it, add it all up. You rarely need
// to hand-write these loops.

int multiply(int a, int b) {
    return a * b;
}

int main() {
    std::vector<int> values{5, 2, 8, 1, 9, 3, 7};

    // std::ranges::sort (C++20) takes the container directly - no
    // begin()/end() pair. Ascending by default.
    std::ranges::sort(values);
    std::print("sorted:");
    for (const int& n : values) {
        std::print(" {}", n);
    }
    std::println("");

    // A lambda as the comparison flips it to descending.
    std::ranges::sort(values, [](int a, int b) { return a > b; });
    std::print("descending:");
    for (const int& n : values) {
        std::print(" {}", n);
    }
    std::println("");

    // binary_search needs the range sorted the same way it searches
    // (ascending here), so sort back first.
    std::ranges::sort(values);
    std::println("contains 8 : {}", std::ranges::binary_search(values, 8));
    std::println("contains 6 : {}", std::ranges::binary_search(values, 6));

    // min_element / max_element return an iterator to the element;
    // dereference it with * to get the value.
    std::println("smallest: {}", *std::ranges::min_element(values));
    std::println("largest : {}", *std::ranges::max_element(values));

    // std::accumulate walks the range building up a single result.
    // Third argument is the starting value - it also fixes the result type.
    int sum{std::accumulate(values.begin(), values.end(), 0)};
    std::println("sum: {}", sum);

    // The optional fourth argument replaces + with any binary operation:
    // a named function...
    int product{std::accumulate(values.begin(), values.end(), 1, multiply)};
    std::println("product (function): {}", product);

    // ...or a lambda right at the call site.
    int product2{std::accumulate(values.begin(), values.end(), 1,
                                 [](int a, int b) { return a * b; })};
    std::println("product (lambda)  : {}", product2);

    // These work on std::array just the same - any contiguous sequence.
    std::array<std::string, 5> words{"pear", "apple", "fig", "kiwi", "plum"};
    std::ranges::sort(words);
    std::print("sorted words:");
    for (const std::string& w : words) {
        std::print(" {}", w);
    }
    std::println("");

    return 0;
}
