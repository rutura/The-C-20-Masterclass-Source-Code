#include <print>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <string>
#include <vector>

void print(auto view) {
    for (auto i : view) { // Computation happens here.
        std::print("{} ", i);
    }
    std::println("");
}

int main() {

    std::vector<int> vi{1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Filter out evens and square them.
    std::print("vi : ");
    print(vi);

    // Raw function composition: views::transform wraps a views::filter
    auto even = [](int n) { return n % 2 == 0; };
    auto my_view = std::views::transform(std::views::filter(vi, even), [](auto n) { return n * n; });
    std::print("vi transformed : ");
    print(my_view);

    std::println("");
    std::println("Pipe operator : ");
    // The pipe operator reads left to right in the order views are applied -
    // exactly equivalent to the nested composition above, but easier to follow.
    auto my_view1 = vi | std::views::filter(even)
                        | std::views::transform([](auto n) { return n * n; });
    std::print("vi transformed : ");
    print(my_view1);

    // Keys are sorted by default in a std::map (unlike unordered_map).
    std::map<std::string, unsigned int> classroom{
        {"John", 11},
        {"Mary", 17},
        {"Steve", 15},
        {"Lucy", 14},
        {"Ariel", 12}
    };

    auto names_view = classroom | std::views::keys;
    std::print("names : ");
    std::ranges::copy(names_view, std::ostream_iterator<std::string>(std::cout, " "));

    std::println("");
    auto ages_view = std::views::values(classroom);
    std::print("ages : ");
    std::ranges::copy(ages_view, std::ostream_iterator<unsigned int>(std::cout, " "));

    // This reverse view wouldn't compile over an unordered_map: reversing
    // needs a bidirectional range, and unordered_map's iterators are only
    // forward iterators.
    std::println("");
    std::print("names in reverse : ");
    std::ranges::copy(std::views::keys(classroom) | std::views::reverse,
                       std::ostream_iterator<std::string>(std::cout, " "));

    std::println("");
    auto before_M = [](const std::string& name) {
        return static_cast<unsigned char>(name[0]) < static_cast<unsigned char>('M');
    };

    std::print("names before M : ");
    std::ranges::copy(classroom | std::views::keys | std::views::filter(before_M),
                       std::ostream_iterator<std::string>(std::cout, " "));
    std::println("");

    return 0;
}