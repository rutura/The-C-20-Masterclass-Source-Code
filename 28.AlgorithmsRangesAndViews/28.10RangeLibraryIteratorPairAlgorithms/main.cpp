#include <print>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
void print_collection(const T& collection) {
    std::print(" Collection [");
    for (const auto& elt : collection) {
        std::print(" {}", elt);
    }
    std::println("]");
}

int main() {

    // std::ranges:: algorithms also accept an iterator pair, not just a
    // whole range - useful when you only have (or only want) a subrange.
    std::vector<int> numbers{11, 2, 6, 4, 8, 3, 17, 9};
    print_collection(numbers);

    std::println("");
    std::println("std::ranges::all_of() : ");

    auto odd = [](int n) { return n % 2 != 0; };

    if (std::ranges::all_of(numbers.begin(), numbers.end(), odd)) {
        std::println("All elements in numbers are odd");
    } else {
        std::println("Not all elements in numbers are odd");
    }

    std::println("");
    std::println("std::ranges::for_each() : ");
    print_collection(numbers);
    std::ranges::for_each(numbers.begin(), numbers.end(), [](int& n) { n *= 2; });
    print_collection(numbers);

    std::println("");
    std::println("std::ranges::sort() : ");
    print_collection(numbers);
    std::ranges::sort(numbers.begin(), numbers.end());
    print_collection(numbers);

    std::println("");
    std::println("std::ranges::find() : ");
    auto odd_n_position = std::ranges::find_if(numbers.begin(), numbers.end(), odd);

    if (odd_n_position != numbers.end()) {
        std::println("numbers contains at least one odd number : {}", *odd_n_position);
    } else {
        std::println("numbers does not contain any odd number");
    }

    std::println("");
    std::print("numbers : ");
    std::ranges::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::println("");

    return 0;
}