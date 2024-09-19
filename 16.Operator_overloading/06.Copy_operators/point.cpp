#include "point.h"
#include "car.h"

double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

Point::Point(const Point &p)
{
  if (this != &p) {
    delete p_data;
    p_data = new int(*(p.p_data));
    m_x = p.m_x;
    m_y = p.m_y;
  }
}

Point &Point::operator=(const Point &right_operand)
{
  fmt::println("Copy assignment operator called");
  if (this != &right_operand) {
    delete p_data;
    p_data = new int(*(right_operand.p_data));
    m_x = right_operand.m_x;
    m_y = right_operand.m_y;
  }
  return *this;
}


//Car copy constructor
void Point::operator=(const Car &c)
{
  m_x = m_y = c.get_speed();
  *p_data = c.get_speed();
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
  os << "Point [ x : " << p.m_x << ", y : " << p.m_y << " data : " << *(p.p_data) << "]";
  return os;
}