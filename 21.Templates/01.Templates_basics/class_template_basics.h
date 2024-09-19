#pragma once

namespace class_template_basics {

//The requirement is that the type T must support the + operator.
//The types of the coordinates also must be the same.
template<typename T> class Point
{
  friend Point operator+(const Point a, const Point b) { return Point(a.x + b.x, a.y + b.y); }
  T x;
  T y;

public:
  Point(T x, T y)
    : x(x), y(y) {}

  T get_x() const { return x; }
  T get_y() const { return y; }
};

}// namespace class_template_basics