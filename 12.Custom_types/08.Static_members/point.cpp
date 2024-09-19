#include "point.h"

#include <fmt/format.h>


/* #1.
//Implementations
// Initialize static member var
size_t Point::m_point_count{ 0 };

Point::Point(double x, double y) : m_x{ x }, m_y{ y }
{
  fmt::println("Point constructor called");
  ++m_point_count;
}

// Point Constructor
Point::Point(double xy_coord) : Point(xy_coord, xy_coord) {}
// Default constructor
Point::Point() : Point(0.0, 0.0) {}
// Point Copy Constructor
Point::Point(const Point &point) : Point{ point.m_x, point.m_y } {}
// Point Destructor
Point::~Point() { --m_point_count; }
// Function to calculate distance from the point(0,0)
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
*/



/*#2.
//Implementations

Point::Point(double x, double y) : m_x{ x }, m_y{ y }
{
  fmt::println("Point constructor called");
  ++m_point_count;
}

// Point Constructor
Point::Point(double xy_coord) : Point(xy_coord, xy_coord) {}
// Default constructor
Point::Point() : Point(0.0, 0.0) {}
// Point Copy Constructor
Point::Point(const Point &point) : Point{ point.m_x, point.m_y } {}
// Point Destructor
Point::~Point() { --m_point_count; }
// Function to calculate distance from the point(0,0)
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
 */


//Implementations
Point::Point(double x, double y) : m_x(x), m_y(y)
{
  fmt::println("Constructing Point [ m_x : {}, m_y:{}]", m_x, m_y);
  ++m_point_count;
}

Point::Point(double xy_coord) : Point(xy_coord, xy_coord) { fmt::println("Point single param constructor called"); }

Point::Point() : Point(0.0, 0.0) { fmt::println("Point default constructor called"); }

Point::Point(const Point &point) : Point(point.m_x, point.m_x)
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

void Point::print_info(const Point &p)
{ fmt::println("Point : [ m_x: {}, m_y: {}]", p.m_x, p.m_y); }
