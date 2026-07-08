#include <print>
#include <algorithm>
#include <vector>

struct Sum {
    void operator()(int n) { sum += n; }
    int sum{0};
};

int main() {

    std::vector<int> nums{3, 4, 2, 8, 15, 267};

    auto print = [](const int& n) {
        std::print(" {}", n);
    };

    // Print each element: lambda predicate
    std::for_each(nums.begin(), nums.end(), print);
    std::println("");

    std::println("---------------------------------");

    // Predicate that modifies elements in place
    std::for_each(nums.begin(), nums.end(), [](int& n) { n++; });
    std::for_each(nums.begin(), nums.end(), print);
    std::println("");

    std::println("---------------------------------");

    // std::for_each returns the (possibly-moved-from) functor it was given -
    // useful for a stateful functor like Sum, since the accumulated result
    // comes back out through the return value.
    Sum s;
    s = std::for_each(nums.begin(), nums.end(), s);
    std::println("result : {}", s.sum);

    std::println("---------------------------------");

    // Same accumulation, but with a lambda capturing a local by reference
    // instead of a named functor type.
    int our_result{0};
    std::for_each(nums.begin(), nums.end(), [&our_result](int n) { our_result += n; });
    std::println("result : {}", our_result);

    return 0;
}