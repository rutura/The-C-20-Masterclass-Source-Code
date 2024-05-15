#include "point.h"
#include "number.h"

Point::Point(double x, double y) : m_x(x), m_y(y) {}

/*
Point::Point(const Number& n){
    fmt::println( "Point Constructor from Number called..." );
    m_x = m_y = n.get_wrapped_int();
}
*/


void Point::operator=(const Number &n)
{
  fmt::println("Point Copy assignment operator from Number called...");
  m_x = m_y = n.get_wrapped_int();
}


// Point::Point(const Point& p):Point(p.m_x, p.m_y)
Point::Point(const Point &p)
{
  fmt::println("Copy constructor called to copy point {}", p);
  if (this != &p) {
    m_x = p.m_x;
    m_y = p.m_y;
  }
}
