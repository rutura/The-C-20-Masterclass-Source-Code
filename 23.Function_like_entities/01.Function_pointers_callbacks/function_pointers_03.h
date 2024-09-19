#pragma once

#include "boxcontainer.h"

#include <string>


namespace function_pointers_03 {

// Templated type alias
template<typename T> using compare_T = bool (*)(const T &, const T &);

template<typename T> T get_best(const box::BoxContainer<T> &collection, compare_T<T> comparator)
{
  T best = collection.get_item(0);
  for (size_t i{}; i < collection.size(); ++i) {
    if (comparator(collection.get_item(i), best)) { best = collection.get_item(i); }
  }
  return best;
}

bool larger_in_size(const std::string &str1, const std::string &str2);


bool greater_lexicographically(const std::string &str1, const std::string &str2);

bool larger_int(const int &param1, const int &param2);


template<typename T> bool smaller(const T &param1, const T &param2)
{
  if (param1 < param2) { return true; }
  return false;
}

}//namespace function_pointers_03