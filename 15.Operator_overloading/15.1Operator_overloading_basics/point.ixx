module;

#include <fmt/format.h>
#include <cmath>
#include <cassert>

export module point;

//#1: Overload operator+ as a member
/*
export class Point
{
public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;

  // Member
//   Point operator+(const Point& right_operand){
//       return Point(this->m_x + right_operand.m_x ,
//                     this->m_y + right_operand.m_y );
//   }

  Point operator+(const Point &right_operand);

  void print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
};

//Implementation

double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

Point Point::operator+(const Point &right_operand)
{
  return Point(this->m_x + right_operand.m_x, this->m_y + right_operand.m_y);
}
*/



//#2: Overload operator+ as a non_member
/*
export class Point
{
  friend Point operator+(const Point &left, const Point &right);

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;

  void print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
};


// inline Point operator+(const Point &left, const Point &right)
// {
//   return Point(left.m_x + right.m_x, left.m_y + right.m_y);
// }


//Implemantations
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

Point operator+(const Point& left, const Point& right){
        return Point(left.m_x + right.m_x , left.m_y + right.m_y );
}
*/


//#3: Overload the subscript operator for Point
/*
export class Point
{
public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;

  double operator[](size_t index) const
  {
    assert((index == 0) || (index == 1));
    if (index == 0) {
      return m_x;
    } else {
      return m_y;
    }
  }

  void print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};// 0
  double m_y{};// 1
};

//Implementation
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
*/


//#4: Overload the subscript operator for reading and writting
/*
export class Point
{
public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;

  double &operator[](size_t index)
  {
    assert((index == 0) || (index == 1));
    return (index == 0) ? m_x : m_y;
  }

  void print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};// 0
  double m_y{};// 1
};

//Implementations
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
*/


//#5: Subscript operator for collection types