module;

#include <iostream>
#include <cmath>
#include <fmt/core.h>

export module point;



export class Point
{
  friend std::ostream &operator<<(std::ostream &os, const Point &p);    //Insertion
  friend std::istream &operator>>(std::istream &is, Point &p);          // Extraction
  friend struct fmt::formatter<Point>; // Make the formatter a friend

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;

//   std::ostream& operator<< (std::ostream& os){
//           os << "Point [ x : " << m_x << ", y : " << m_y << "]";
//           return os;
//   }

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
};

//Insertion
inline std::ostream &operator<<(std::ostream &os, const Point &p)
{
  os << "Point [ x : " << p.m_x << ", y : " << p.m_y << "]";
  return os;
}

//Exctraction
inline std::istream &operator>>(std::istream &is, Point &p)
{
  double x;
  double y;

  fmt::print("Please type in the coordinates for the point\n");
  fmt::print("order [x,y], separated by spaces : ");

  std::cin >> x >> y;
  p.m_x = x;
  p.m_y = y;

  return is;
}

//Implementations
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }