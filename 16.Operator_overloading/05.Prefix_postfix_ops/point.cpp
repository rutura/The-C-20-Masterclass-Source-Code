#include "point.h"

#include <fmt/format.h>
#include <cmath>

//#1: unary prefix operator+ as member

std::ostream &operator<<(std::ostream &os, const Point &p)
{
  os << "Point [ x: " << p.m_x << ", y: " << p.m_y << "]";
  return os;
}


//Implementation
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

//#2: Prefix operator+ done as a non-member
/*
void operator++(Point& operand){
        ++(operand.m_x);
        ++(operand.m_y);
}
*/

//#2: Prefix operator+ done as a non-member
void operator++(Point &operand)
{
  ++(operand.m_x);
  ++(operand.m_y);
}


//#3: Postfix operator++ done as non-member
Point operator++(Point &operand, int)
{
  Point local_point(operand);
  ++operand;
  return local_point;
}
