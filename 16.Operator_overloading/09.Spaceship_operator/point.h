#pragma once


#include <fmt/format.h>

class Point
{
  friend std::ostream &operator<<(std::ostream &out, const Point &p);

public:
  Point() = default;
  Point(double x, double y) : m_x{ x }, m_y{ y } {}

  Point(double x_y) : Point{ x_y, x_y } {}
  // Operators
  bool operator==(const Point &other) const;
  // bool operator!=(const Point& other) const;
  double x() const { return m_x; }
  double y() const { return m_y; }
  double length() const;// Function to calculate distance from the point(0,0)
private:
  double m_x{};
  double m_y{};
};