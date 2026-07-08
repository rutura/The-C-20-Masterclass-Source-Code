#include <print>
#include <algorithm>
#include <cstdlib>
#include <list>

int main() {

    std::list<int> v{3, 400, 51, 6, 7, 23, 56, 71};

    // max_element/min_element return an iterator to the found element
    auto result = std::max_element(v.begin(), v.end());
    std::println("max element is : {}", *result);

    result = std::min_element(v.begin(), v.end());
    std::println("min element is : {}", *result);

    std::println("----------");

    // Closest/furthest from a target value, via a custom comparator
    int number_to_find{100};

    auto distance = [number_to_find](int x, int y) {
        return (std::abs(x - number_to_find) < std::abs(y - number_to_find));
    };

    result = std::min_element(v.begin(), v.end(), distance);
    std::println("{} is closest to {}", *result, number_to_find);

    result = std::max_element(v.begin(), v.end(), distance);
    std::println("{} is furthest from {}", *result, number_to_find);

    std::println("--------------------------------");

    // std::minmax_element finds both in one pass, returned as a pair -
    // structured bindings unpack it directly into near/far.
    const auto [near, far] = std::minmax_element(v.begin(), v.end(), distance);
    std::println("{} is closest to {}", *near, number_to_find);
    std::println("{} is furthest from {}", *far, number_to_find);

    return 0;
}