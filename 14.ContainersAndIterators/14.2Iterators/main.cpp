#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <print>
#include <string>
#include <vector>

// A function that works for ANY container, because it only uses what every
// iterator can do. std::distance and std::advance are fast for a vector and
// walk step by step for a list, but the code is the same.
template <typename Iterator>
Iterator middle(Iterator first, Iterator last) {
    Iterator it{first};
    std::advance(it, std::distance(first, last) / 2);
    return it;
}

int main() {

    std::vector<double> readings{18.5, 19.0, 21.5, 20.0, 22.5};

    // begin() points at the first element, end() points ONE PAST the last.
    // The range [begin, end) is "half open": empty exactly when begin == end.
    // Never dereference end().
    std::println("--- walking with iterators");
    for (auto it{readings.begin()}; it != readings.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println();

    // A range-based for loop (7.2) is this loop, written for you.
    // *it reads the element, ++it moves to the next one.

    // find returns an iterator, and end() means "not found".
    auto found{std::find(readings.begin(), readings.end(), 21.5)};
    if (found != readings.end()) {
        std::println("found 21.5 at index {}", std::distance(readings.begin(), found));
    }

    std::println("\n--- const and reverse");
    for (auto it{readings.cbegin()}; it != readings.cend(); ++it) {
        // *it = 0.0;           // error: a const_iterator cannot change the element
    }
    for (auto it{readings.rbegin()}; it != readings.rend(); ++it) {
        std::print("{} ", *it);                       // ++ on a reverse iterator moves BACKWARD
    }
    std::println();

    // Iterators are not only for vectors.
    std::list<std::string> stations{"north", "south", "east", "west"};
    std::forward_list<int> ids{1, 2, 3, 4, 5};

    std::println("\n--- the same tools on other containers");
    std::println("middle of the vector: {}", *middle(readings.begin(), readings.end()));
    std::println("middle of the list:   {}", *middle(stations.begin(), stations.end()));
    std::println("middle of the forward_list: {}", *middle(ids.begin(), ids.end()));

    // What an iterator can do depends on the container. From weakest to strongest:
    //
    //   input / output   one pass:  ++ and *                   reading from a stream
    //   forward          many passes, ++ only                  std::forward_list
    //   bidirectional    also --                               std::list, std::map, std::set
    //   random access    also it + n, it[n], it1 - it2, <      std::deque, std::vector
    //   contiguous       random access, elements side by side  std::vector, std::array
    static_assert(std::forward_iterator<std::forward_list<int>::iterator>);
    static_assert(!std::bidirectional_iterator<std::forward_list<int>::iterator>);
    static_assert(std::bidirectional_iterator<std::list<int>::iterator>);
    static_assert(!std::random_access_iterator<std::list<int>::iterator>);
    static_assert(std::random_access_iterator<std::vector<int>::iterator>);
    static_assert(std::contiguous_iterator<std::vector<int>::iterator>);

    std::println("\n--- what each category allows");
    auto v_it{readings.begin()};
    std::println("vector:  begin() + 3 is {}", *(v_it + 3));                 // jump, cheap
    auto l_it{stations.begin()};
    // l_it + 3                          // error: a list iterator cannot jump
    std::println("list:    std::next(begin(), 3) is {}", *std::next(l_it, 3)); // walks 3 steps

    // std::sort needs random access, so it works on a vector but not on a
    // std::list. That is why list has its own member function sort().
    stations.sort();
    std::println("sorted list: {}", stations.front());
    return 0;
}
