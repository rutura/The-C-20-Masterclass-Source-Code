#pragma once

#include <fmt/format.h>
#include <cmath>
#include <cassert>

//#1: Overload operator+ as a member
class Point
{
public:
  Point() = default;
  Point(double x, double y) ;
  ~Point() = default;

  // Member
   // Point operator+(const Point& right_operand);

  Point operator+(const Point &right_operand);

  void print_info();

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
};


//#2: Overload operator+ as a non_member
/*class Point
{
  friend Point operator+(const Point &left, const Point &right);

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;

  void print_info();

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
};*/

//#3: Overload the subscript operator for Point
/*
class Point
{
public:
  Point() = default;
  Point(double x, double y);
  ~Point() = default;

  double operator[](size_t index) const;

  void print_info();

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};// 0
  double m_y{};// 1
};
*/

//#4: Overload the subscript operator for reading and writting
/*
class Point
{
public:
  Point() = default;
  Point(double x, double y);
  ~Point() = default;

  double &operator[](size_t index);

  void print_info();

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};// 0
  double m_y{};// 1
};
*/

//#5: Subscript operator for collection types