#pragma once

#include <fmt/format.h>

class Point
{
  friend std::ostream &operator<<(std::ostream &os, const Point &p);
  friend Point operator+(const Point &left, const Point &right);
  friend Point operator-(const Point &left, const Point &right);
  friend Point &operator+=(Point &left, const Point &right);
  friend Point &operator-=(Point &left, const Point &right);

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
};
