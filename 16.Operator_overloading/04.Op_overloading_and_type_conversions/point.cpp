#include "point.h"



std::ostream &operator<<(std::ostream &os, const Point &p)
{
  os << "Point [ x : " << p.m_x << ", y : " << p.m_y << "]";
  return os;
}

Point &operator+=(Point &left, const Point &right)
{
  left.m_x += right.m_x;
  left.m_y += right.m_y;
  return left;
}

Point &operator-=(Point &left, const Point &right)
{
  left.m_x -= right.m_x;
  left.m_y -= right.m_y;
  return left;
}


Point operator+(const Point &left, const Point &right)
{
  Point p(left);
  return p += right;
}

Point operator-(const Point &left, const Point &right)
{
  Point p(left);
  return p -= right;
}


//Implementations

/*
Point::Point(const Number& n)
: Point(static_cast<double>(n.get_wrapped_int()) ,
        static_cast<double>(n.get_wrapped_int()))
{
    fmt::println( "Using the Point constructor" );
}
*/

double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
