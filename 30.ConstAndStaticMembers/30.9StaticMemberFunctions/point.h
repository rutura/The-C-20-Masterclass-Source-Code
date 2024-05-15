#ifndef POINT_H
#define POINT_H

#include <fmt/format.h>

class Point
{
public:
  // Constructors
  Point(double x, double y);

  Point(double xy_coord);// Point Constructor
  Point();// Default constructor
  Point(const Point &point);// Point Copy Constructor
  ~Point();// Point Destructor


  double length() const;// Function to calculate distance from the point(0,0)

  static size_t get_point_count() { return m_point_count; }

  static void print_info(const Point &p) { fmt::println("Point : [ m_x : {}, m_y: {}]", p.m_x, p.m_y); }

private:
  double m_x;
  double m_y;
  inline static size_t m_point_count{};
};


#endif// POINT_H
