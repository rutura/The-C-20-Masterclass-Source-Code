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

    // These are the exact same algorithms from chapter 31 (std::all_of,
    // std::for_each, std::sort, std::find_if, std::copy) - here as their
    // std::ranges:: versions, which take a whole range directly instead of
    // an iterator pair.
    std::vector<int> numbers{11, 2, 6, 4, 8, 3, 17, 9};
    print_collection(numbers);

    std::println("");
    std::println("std::ranges::all_of() : ");

    auto odd = [](int n) { return n % 2 != 0; };

    if (std::ranges::all_of(numbers, odd)) {
        std::println("All elements in numbers are odd");
    } else {
        std::println("Not all elements in numbers are odd");
    }

    std::println("");
    std::println("std::ranges::for_each() : ");
    print_collection(numbers);
    std::ranges::for_each(numbers, [](int& n) { n *= 2; });
    print_collection(numbers);

    std::println("");
    std::println("std::ranges::sort() : ");
    print_collection(numbers);
    std::ranges::sort(numbers);
    print_collection(numbers);

    std::println("");
    std::println("std::ranges::find() : ");
    auto odd_n_position = std::ranges::find_if(numbers, odd);

    if (odd_n_position != numbers.end()) {
        std::println("numbers contains at least one odd number : {}", *odd_n_position);
    } else {
        std::println("numbers does not contain any odd number");
    }

    // std::ranges::copy still writes through an output iterator, so an
    // ostream_iterator - not std::print - is the way to stream it out.
    std::println("");
    std::print("numbers : ");
    std::ranges::copy(numbers, std::ostream_iterator<int>(std::cout, " "));
    std::println("");

    return 0;
}