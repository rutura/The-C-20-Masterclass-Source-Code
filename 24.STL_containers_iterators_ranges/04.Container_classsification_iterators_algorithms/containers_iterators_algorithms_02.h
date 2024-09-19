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
#pragma once

#include <set>
#include <algorithm>
#include <numeric>
#include <fmt/format.h>


namespace containers_iterators_algorithms_02 {

inline void use_set()
{
  std::set<int> mySet = { 1, 3, 5, 7, 9 };

  // Find an element
  auto it = mySet.find(5);
  if (it != mySet.end()) { fmt::print("Found: {}\n", *it); }

  // Perform set union with another set
  std::set<int> otherSet = { 2, 4, 6, 8, 10 };
  std::set<int> resultSet;
  std::set_union(mySet.begin(),
    mySet.end(),
    otherSet.begin(),
    otherSet.end(),
    std::inserter(resultSet, resultSet.begin()));

  fmt::print("Set union: ");
  for (int n : resultSet) { fmt::print("{} ", n); }
  fmt::print("\n");

  // Calculate the sum of all elements
  int sum = std::accumulate(mySet.begin(), mySet.end(), 0);
  fmt::print("Sum of elements: {}\n", sum);
}

}// namespace containers_iterators_algorithms_02