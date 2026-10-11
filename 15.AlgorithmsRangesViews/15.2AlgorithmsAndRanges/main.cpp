#include <algorithm>
#include <functional>
#include <list>
#include <print>
#include <vector>

// The standard algorithms are functions that work on ANY container through
// its iterators (14.2). Each one exists in two forms:
//
//   std::find(first, last, value)       the classic form: an iterator PAIR
//   std::ranges::find(range, value)     the C++20 form: the container itself
//
// Both do the same work. The ranges form is shorter, checks more at compile
// time, and accepts "projections" (15.8). Prefer it in new code.

int main() {

    std::vector<double> temperatures{18.5, 24.0, 21.5, 12.5, 16.0};

    std::println("--- the same search, two forms");
    auto classic{std::find(temperatures.begin(), temperatures.end(), 21.5)};
    auto modern{std::ranges::find(temperatures, 21.5)};
    std::println("classic: index {}   ranges: index {}", classic - temperatures.begin(), modern - temperatures.begin());

    // Both return an iterator, and end() means "not found" (14.2).
    if (std::ranges::find(temperatures, 99.0) == temperatures.end()) {
        std::println("99.0 is not there");
    }

    // An iterator pair can describe just a PART of a container, which is what
    // makes the classic form flexible: here, sort only the first three.
    // (The ranges form has a neat way to say this too, with views: 15.9.)
    std::println("\n--- a part of a container");
    std::vector<double> sorted_part{temperatures};
    std::sort(sorted_part.begin(), sorted_part.begin() + 3);
    std::print("first three sorted:");
    for (double t : sorted_part) {
        std::print(" {}", t);
    }
    std::println();

    // Many algorithms work on lists and other containers too, as long as their
    // iterators are strong enough (14.2).
    std::list<double> as_list{temperatures.begin(), temperatures.end()};
    std::println("\n--- other containers");
    std::println("find in a list: {}", *std::ranges::find(as_list, 12.5));
    // std::ranges::sort(as_list);   // error: a list has no random access iterators
    as_list.sort();                  // the list's own member function (14.5)
    std::println("sorted list starts with {}", as_list.front());

    // The ranges algorithms state their requirements in their declaration, so
    // a mistake like the one above is reported at your call as "the range does
    // not satisfy random_access_range", and not as dozens of lines inside the
    // library.

    // What the algorithms return depends on what they know.
    std::println("\n--- return values");
    auto [smallest, largest]{std::ranges::minmax(temperatures)};           // both values, in one pass
    std::println("minmax: {} and {}", smallest, largest);
    std::println("max_element points at {}", *std::ranges::max_element(temperatures));
    std::vector<double> copy(temperatures.size());
    auto result{std::ranges::copy(temperatures, copy.begin())};            // where input ended, where output ended
    std::println("copy returned two iterators: the output now ends at index {}", result.out - copy.begin());

    // Passing a temporary container to an algorithm that returns an iterator
    // into it is caught at compile time (15.10).

    // An algorithm never changes the SIZE of a container. It only moves values
    // around through iterators. To add or remove elements you call the
    // container's own functions (15.5) or write through an inserter (15.4).

    // The families, as a map of the chapter:
    //   non-modifying   find, count, any_of, equal, mismatch ...        15.3
    //   modifying       copy, transform, fill, replace, reverse ...      15.4
    //   removing        remove, remove_if, unique, erase_if              15.5
    //   sorting         sort, partition, nth_element, binary search ...  15.6
    //   numeric         reduce, partial_sum, transform_reduce ...        15.7
    return 0;
}
