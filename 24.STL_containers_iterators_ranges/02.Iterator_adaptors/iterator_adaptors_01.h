/*
    C++ supports several iterator adapter types, each providing unique functionality to enhance the behavior of standard iterators. Here is a list of the most common iterator adapters in C++:
        std::back_insert_iterator
        std::front_insert_iterator
        std::insert_iterator
        std::reverse_iterator
        std::move_iterator
        std::ostream_iterator
        std::istream_iterator
        std::istreambuf_iterator
        std::ostreambuf_iterator
        std::counting_iterator (C++20)
        std::common_iterator (C++20)
        std::unreachable_sentinel (C++20)
    We cover the first five in this module.
*/
#pragma once

#include <fmt/format.h>
#include <iterator>
#include <algorithm>
#include <deque>
#include <vector>

namespace iterator_adaptors_01 {

inline void back_insert_iterator_test()
{

  // Initialize a vector with some elements
  std::vector<int> vec = { 1, 2, 3 };
  // Another vector with values to add to vec
  std::vector<int> values_to_add = { 4, 5, 6 };

  // Use std::copy to copy elements from values_to_add to vec
  // std::back_inserter(vec) creates a back_insert_iterator for vec
  std::copy(values_to_add.begin(), values_to_add.end(), std::back_inserter(vec));

  // Output the results
  for (int value : vec) { fmt::println("{}", value); }

}

inline void front_insert_iterator_test()
{

  // Initialize a deque with some elements
  // We use deque here because it supports push_front.
  std::deque<int> deq = { 3, 2, 1 };
  // A vector with values to add to the front of deq
  std::vector<int> values_to_add = { 4, 5, 6 };

  // Use std::copy to copy elements from values_to_add to the front of deq
  // std::front_inserter(deq) creates a front_insert_iterator for deq
  std::copy(values_to_add.begin(), values_to_add.end(), std::front_inserter(deq));

  // Output the results
  for (int value : deq) { fmt::println("{}", value); }

}

inline void insert_iterator_test()
{

  // Initialize a vector with some elements
  std::vector<int> vec = { 1, 2, 6, 7 };
  // A vector with values to insert into vec
  std::vector<int> values_to_add = { 3, 4, 5 };

  // Use std::copy to insert elements from values_to_add at the 3rd position in vec
  // std::inserter(vec, vec.begin() + 2) creates an insert_iterator at the 3rd position
  std::copy(values_to_add.begin(), values_to_add.end(), std::inserter(vec, vec.begin() + 2));

  // Output the results
  for (int value : vec) { fmt::println("{}", value); }

}

inline void reverse_iterator_test()
{

  //Reverse iterators increment backwards.
  // Initialize a vector with some elements
  std::vector<int> vec = { 1, 2, 3, 4, 5 };

  // Use std::for_each to print elements in reverse order
  // vec.rbegin() and vec.rend() provide reverse iterators to the vector
  std::for_each(vec.rbegin(), vec.rend(), [](int value) { fmt::println("{}", value); });
}


}// namespace iterator_adaptors_01