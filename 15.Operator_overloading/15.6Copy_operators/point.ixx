module;

#include <cmath>
#include <fmt/format.h>

export module point;

import car;

export class Point
{
  friend std::ostream &operator<<(std::ostream &os, const Point &p);

public:
  Point() = default;
  Point(double x, double y, int data) : m_x(x), m_y(y), p_data(new int(data)) {}
  Point(const Point &p);// Copy constructor

  Point &operator=(const Point &right_operand)
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

//Car copy constructor
void Point::operator=(const Car &c)
{
  m_x = m_y = c.get_speed();
  *p_data = c.get_speed();
}

inline std::ostream &operator<<(std::ostream &os, const Point &p)
{
  os << "Point [ x : " << p.m_x << ", y : " << p.m_y << " data : " << *(p.p_data) << "]";
  return os;
}


