module;

#include <fmt/format.h>
#include <cmath>

export module point;


//#1: unary prefix operator+ as member

export class Point
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

inline std::ostream &operator<<(std::ostream &os, const Point &p)
{
  os << "Point [ x: " << p.m_x << ", y: " << p.m_y << "]";
  return os;
}


//Implementation
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

//#2: Prefix operator+ done as a non-member
/*
inline void operator++(Point& operand){
        ++(operand.m_x);
        ++(operand.m_y);
}
*/

//#2: Prefix operator+ done as a non-member
export void operator++(Point &operand)
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
