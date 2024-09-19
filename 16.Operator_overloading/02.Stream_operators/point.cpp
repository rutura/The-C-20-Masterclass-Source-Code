#include "point.h"

#include <cmath>


//Insertion
std::ostream &operator<<(std::ostream &os, const Point &p)
{
  os << "Point [ x : " << p.m_x << ", y : " << p.m_y << "]";
  return os;
}

//Exctraction
std::istream &operator>>(std::istream &is, Point &p)
{
  double x;
  double y;

  //fmt::print("Please type in the coordinates for the point\n");
  //fmt::print("order [x,y], separated by spaces : ");

  std::cin >> x >> y;
  p.m_x = x;
  p.m_y = y;

  return is;
}

//Implementations
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }