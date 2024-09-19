/*
    This code contains code that plays with constant iterators.
*/
#pragma once

#include <fmt/format.h>

namespace containers_iterators_03 {

template<typename T> void print_collection(const T &collection)
{

  auto it = collection.begin();

  fmt::print(" [");
  while (it != collection.end()) {
    fmt::print(" {}", *it);
    ++it;
  }
  fmt::println(" ]");
}

}// namespace containers_iterators_03