#pragma once

#include <fmt/format.h>

class Point
{
  friend std::ostream &operator<<(std::ostream &out, const Point &p);
  friend bool operator>(const Point &left, const Point &right);
  friend bool operator>=(const Point &left, const Point &right);
  friend bool operator==(const Point &left, const Point &right);
  friend bool operator!=(const Point &left, const Point &right);
  friend bool operator<(const Point &left, const Point &right);
  friend bool operator<=(const Point &left, const Point &right);

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;
  // Operators: can also do them as members.
  /*
  bool operator> (const Point& other) const;
  bool operator< (const Point& other) const;
  bool operator>=(const Point& other) const;
  bool operator<=(const Point& other) const;
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
  */
  double length() const;// Function to calculate distance from the point(0,0)
private:
  double m_x{};
  double m_y{};
};