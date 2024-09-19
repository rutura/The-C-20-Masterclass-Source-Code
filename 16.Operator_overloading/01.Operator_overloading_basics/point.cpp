#include "point.h"

//#1: Overload operator+ as a member

//Implementation
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }


// Point Point::operator+(const Point& right_operand)
// {
//   return Point(this->m_x + right_operand.m_x ,
//                 this->m_y + right_operand.m_y );
// }

Point::Point(double x, double y) : m_x(x), m_y(y) {}

Point Point::operator+(const Point &right_operand)
{
  return Point(this->m_x + right_operand.m_x, this->m_y + right_operand.m_y);
}

void Point::print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

//#2: Overload operator+ as a non_member

/*
// inline Point operator+(const Point &left, const Point &right)
// {
//   return Point(left.m_x + right.m_x, left.m_y + right.m_y);
// }


void Point::print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

//Implemantations
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

Point operator+(const Point& left, const Point& right){
  return Point(left.m_x + right.m_x , left.m_y + right.m_y );
}
*/


//#3: Overload the subscript operator for Point
/*
//Implementation
Point::Point(double x, double y):  m_x(x), m_y(y) {}

double Point::operator[](size_t index) const
{
  assert((index == 0) || (index == 1));
  if (index == 0) { return m_x; } else { return m_y; }
}

void Point::print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
*/


//#4: Overload the subscript operator for reading and writting

/*Point::Point(double x, double y): m_x(x), m_y(y) {}

double & Point::operator[](size_t index)   {
  assert((index == 0) || (index == 1));
  return (index == 0) ? m_x : m_y;
}

void Point::print_info(){ fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

double Point::length() const {
{
  return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0);
}*/