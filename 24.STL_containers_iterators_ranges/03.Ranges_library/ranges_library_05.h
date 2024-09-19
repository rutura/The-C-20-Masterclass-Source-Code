#pragma once

#include <fmt/format.h>

namespace ranges_library_05 {

void print(auto view)
{
  for (auto i : view) {
    // Computation happens here.
    fmt::print("{} ", i);
  }
  fmt::println("");
}

}// namespace ranges_library_05