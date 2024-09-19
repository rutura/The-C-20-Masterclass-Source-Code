#pragma once
#include <ostream>

class Point
{
  friend std::ostream &operator<<(std::ostream &os, const Point &p);
  friend void operator++(Point &operand);
  friend Point operator++(Point &operand, int);

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}

  //prefix operator done as a member
  /*
  void operator++()
  {
    ++m_x;
    ++m_y;
  }
  */

  //Postfix done as a member
  /*
  Point operator++(int){
      Point local_point(*this);
      ++(*this);
      return local_point;
  }
  */

  ~Point() = default;

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
};
