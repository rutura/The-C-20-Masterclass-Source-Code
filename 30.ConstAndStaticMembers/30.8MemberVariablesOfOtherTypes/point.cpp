#include "point.h"
#include <cmath>
#include <fmt/format.h>

size_t Point::m_point_count{};// Initialize static member of Point class to 0

Integer Point::i6{ 6 };
const Integer Point::i7{ 7 };


Point::Point(double x, double y) : p_i5(new Integer(5)), m_x(x), m_y(y)
{
  fmt::println("Constructing Point [ m_x : {}, m_y: {} ]", m_x, m_y);
  ++m_point_count;
}

Point::Point(double xy_coord) : Point(xy_coord, xy_coord) { fmt::println("Point single param constructor called"); }

Point::Point() : Point(0.0, 0.0) { fmt::println("Point default constructor called"); }

Point::Point(const Point &point) : m_x(point.m_x)
{
  // Copy constructor
  fmt::println("Copy constructor called");
  ++m_point_count;// Creating a copy object. So we increment
}

Point::~Point()
{
  // Destructor
  fmt::println("Destroying point object. ");
  // We destroy a point object , so we decrement
  --m_point_count;

  fmt::println(" Current point count : {}", m_point_count);
}

double Point::length() const
{
  // Function to calculate distance from the point(0,0)
  return sqrt(pow(m_x - 0.0, 2) + pow(m_y - 0.0, 2));
}
