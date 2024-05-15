#ifndef POINT_H
#define POINT_H

#include <fmt/format.h>

class Point
{
private:
  double *x{};
  double *y{};

  void invalidate()
  {
    x = nullptr;
    y = nullptr;
  }

public:
  Point() = delete;
  Point(double x_param, double y_param);
  ~Point();
  // Copy constructor
  Point(const Point &source_point) = delete;

  // Move constructor
  Point(Point &&source_point) = delete;


  // Setters
  void set_x(double x)
  {
    *(this->x) = x;// Dereference and assign
  }
  void set_y(double y)
  {
    *(this->y) = y;// Dereference and assign
  }

  // Getters
  double *get_x() const { return x; }

  double *get_y() const { return y; }

  double *steal_x()
  {
    double *new_x = x;
    x = nullptr;
    return new_x;
  }

  double *steal_y()
  {
    double *new_y = y;
    y = nullptr;
    return new_y;
  }

  // Utilities
  void print_info() const { fmt::println("Point [ x : {}, y: {}]", *x, (*y)); }
};

#endif// POINT_H
