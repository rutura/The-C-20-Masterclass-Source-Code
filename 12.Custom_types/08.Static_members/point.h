#pragma once

#include <cmath>

// #1: Static members
/*
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

  size_t get_point_count() const { return m_point_count; }

  void print_info() const { fmt::println("Point  [ &m_x: {}, &m_y: {} ", fmt::ptr(&m_x), fmt::ptr(&m_y)); }

private:
  double m_x;
  double m_y;
  static size_t m_point_count;
};
*/

// #2: Inline static member variables
/*
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

  size_t get_point_count() const { return m_point_count; }

  void print_info() const { fmt::println("Point  [ &m_x : {}, &m_y: {} ", fmt::ptr(&m_x), fmt::ptr(&m_y)); }

private:
  double m_x;
  double m_y;
  inline static size_t m_point_count{};// C++17
};
*/



// #4: Static member functions
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

  static void print_info(const Point &p);

private:
  double m_x;
  double m_y;
  inline static size_t m_point_count{};
};