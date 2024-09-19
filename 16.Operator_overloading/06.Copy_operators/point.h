#pragma once

#include <cmath>
#include <fmt/format.h>

class Car;

class Point
{
  friend std::ostream &operator<<(std::ostream &os, const Point &p);

public:
  Point() = default;

  Point(double x, double y, int data)
    : m_x(x), m_y(y), p_data(new int(data)) {}

  Point(const Point &p);// Copy constructor

  Point &operator=(const Point &right_operand);
  //Car copy constructor
  void operator=(const Car &c);

  void set_data(int data) { *p_data = data; }
  ~Point() { delete p_data; }

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
  int *p_data;
};