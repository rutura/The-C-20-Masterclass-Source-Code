#pragma once

#include <fmt/format.h>

namespace ranges_library_02 {

template<typename T> void print_collection(const T &collection)
{

  fmt::print(" Collection [");
  for (const auto &elt : collection) { fmt::print(" {}", elt); }
  fmt::print("]");
}

}// namespace ranges_library_02