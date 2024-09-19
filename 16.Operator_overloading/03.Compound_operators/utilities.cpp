#include "point.h"
#include "utilities.h"
#include <fmt/format.h>
#include <iostream>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void compound_operators()
{
  Point p1(10, 10);
  Point p2(20, 20);
  Point p3(5, 5);

  auto p1_plus_p2 = p1 + p2;
  auto p2_minus_p3 = p2 - p3;

  std::cout << "p1 + p2: " << p1_plus_p2 << "\n";
  std::cout << "p2 - p3: " << p2_minus_p3 << "\n";

  std::cout << "------" << "\n";

  p1 += p2;
  p2 -= p3;

  std::cout << "point1: " << p1 << "\n";
  std::cout << "point2: " << p2 << "\n";
}