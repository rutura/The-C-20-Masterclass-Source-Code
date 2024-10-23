/*

    Associative Containers in C++: set, map, multiset, multimap

    1. std::set
        . Iterators Provided: Bidirectional iterators.
        . Common Algorithms: std::find, std::set_union, std::accumulate.
            . std::find works with which iterator? 
            . std::set_union 
            . std::accumulate 

    2. std::map
            . Iterators Provided: Bidirectional iterators.
            . Common Algorithms: std::for_each, std::transform, std::copy_if.
                . std::for_each
                . std::transform  
                . std::copy_if

    3. std::multiset
            . Iterators Provided: Bidirectional iterators.
            . Common Algorithms: std::count, std::partial_sum, std::remove.
                . std::count 
                . std::partial_sum 
                . std::remove works with 

    4. std::multimap

            . Iterators Provided: Bidirectional iterators.
            . Common Algorithms: std::equal_range, std::find_if, std::distance.
                . std::equal_range 
                . std::find_if 
                . std::distance


*/

module;

#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <fmt/format.h>
#include <iterator>

export module containers_iterators_algorithms_02;

namespace containers_iterators_algorithms_02{

    export void use_set(){
        std::set<int> my_set = {1, 3, 5, 7, 9};

        // Find an element
        auto it = my_set.find(5);
        if (it != my_set.end()) {
            fmt::print("Found: {}\n", *it);
        }

        // Perform set union with another set
        std::set<int> other_set = {2, 4, 6, 8, 10};
        std::set<int> result_set;
        std::set_union(my_set.begin(), my_set.end(),
                    other_set.begin(), other_set.end(),
                    std::inserter(result_set, result_set.begin()));

        fmt::print("Set union: ");
        for (int n : result_set) {
            fmt::print("{} ", n);
        }
        fmt::print("\n");

        // Calculate the sum of all elements
        int sum = std::accumulate(my_set.begin(), my_set.end(), 0);
        //There is no ranges version of accumulate: https://stackoverflow.com/questions/63933163/why-didnt-accumulate-make-it-into-ranges-for-c20
        fmt::print("Sum of elements: {}\n", sum);
    }

}   // namespace containers_iterators_algorithms_02