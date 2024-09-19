#pragma once

#include <fmt/format.h>

namespace lambdas_02 {

inline void capture_by_value_under_the_hood()
{

  int a{ 7 };
  int b{ 3 };
  int some_var{ 28 };// Not captured by the [=] lambda, so it won't set up a member var
  // for this
  double some_other_var{ 55.5 };// Not captured by the [=] lambda, so it won't set up
  // a member var for this.

  // Capturing  everything by value
  auto func = [=](int c, int d) {
    fmt::println("Captured values : ");
    fmt::println("a : {}", a);
    fmt::println("b : {}", b);


    fmt::println("Parameters : ");
    fmt::println("c : {}", c);
    fmt::println("d : {}", d);
  };
  func(10, 20);

  fmt::println("----");
  func(20, 30);
}

}// namespace lambdas_02