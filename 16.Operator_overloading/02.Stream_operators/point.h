#pragma once

#include <iostream>

class Point
{
  friend std::ostream &operator<<(std::ostream &os, const Point &p);    //Insertion
  friend std::istream &operator>>(std::istream &is, Point &p);          // Extraction

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
