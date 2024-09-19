#pragma once

#include <fmt/format.h>

namespace templates_and_friendship_01 {

class Point
{
  int x;
  int y;

public:
  Point(int x, int y)
    : x(x), y(y) {}

  friend void print_point(const Point &p);
};

inline void print_point(const Point &p) { fmt::print("Point: ({}, {})\n", p.x, p.y); }

}// namespace templates_and_friendship_01