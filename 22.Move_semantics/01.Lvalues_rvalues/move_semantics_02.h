/*
    This file contains code that demonstrates rvalue references.
*/
#pragma once

#include <fmt/format.h>


namespace move_semantics_02 {

inline double add(double a, double b) { return a + b; }

inline void try_out_move_semantics()
{

  int x{ 5 };
  int y{ 10 };

  int &&result = x + y;

  double &&outcome = add(10.1, 20.2);

  fmt::println("result : {}", result);
  fmt::println("outcome : {}", outcome);
}

}// namespace move_semantics_02