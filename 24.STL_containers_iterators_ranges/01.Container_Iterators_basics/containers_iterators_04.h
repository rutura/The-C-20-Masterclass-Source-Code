#pragma once

#include <fmt/format.h>
#include <iterator>

namespace containers_iterators_04 {

template<typename T> void print_referenced_value(T it)
{

  //This syntax allows us to retrieve the value contained in the container, which is dynamic.
  //If the container contains int, val will be int, if the container contains std::string, val will be std::string, and so on.
  typename std::iterator_traits<T>::value_type val = *it;
  fmt::println("{}", val);
}

template<typename T> auto custom_find(T begin, T end, typename std::iterator_traits<T>::value_type val)
{

  while (begin != end) {
    if (*begin == val) { return begin; }
    ++begin;
  }
  return end;
}

}// namespace containers_iterators_04