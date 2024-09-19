#include "utilities.h"
#include "point.h"
#include "number.h"

#include <iostream>
#include <fmt/format.h>


void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void logical_operators()
{
  Point point1(10.0, 10.0);
  Point point2(20.0, 20.0);

  std::cout << "point1: " << point1 << "\n";
  std::cout << "point2: " << point2 << "\n";


  fmt::println("point1 > point2 : {}", (point1 > point2));
  fmt::println("point1 < point2 : {}", (point1 < point2));
  fmt::println("point1 >= point2 : {}", (point1 >= point2));
  fmt::println("point1 <= point2 : {}", (point1 <= point2));
  fmt::println("point1 == point2 : {}", (point1 == point2));
  fmt::println("point1 != point2 : {}", (point1 != point2));
}

void logical_ops_implicit_conversions()
{
  Number n1(10);
  Number n2(20);

  fmt::println("n1 < n2 : {}", (n1 < n2));
  fmt::println("15 < n2 : {}", (15 < n2));
  fmt::println("n1 < 25 : {}", (n1 < 5));
}