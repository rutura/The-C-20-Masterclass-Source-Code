#ifndef POINT_H
#define POINT_H

#include <fmt/format.h>

class Number;

class Point
{
  friend std::ostream &operator<<(std::ostream &out, const Point &point);
  friend struct fmt::formatter<Point>;

public:
  Point() = default;
  Point(double x, double y);
  Point(const Point &p);// Copy constructor
  // Point(const Number& n); // Constructor from Number
  ~Point() = default;


  // Copy assignment operator
  Point &operator=(const Point &right_operand)
  {
    fmt::println("Copy assignment operator called");
    if (this != &right_operand) {
      m_x = right_operand.m_x;
      m_y = right_operand.m_y;
    }
    return *this;
  }

  void operator=(const Number &n);// Copy assignment operator for Number

private:
  double m_x{ 0.0 };
  double m_y{ 0.0 };
};

inline std::ostream &operator<<(std::ostream &os, const Point &point)
{
  os << "Point [ x : " << point.m_x << ", y : " << point.m_y << " ]";
  return os;
}

template<> struct fmt::formatter<Point>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Point &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Point [x: {}, y: {}, data: {}]", obj.m_x, obj.m_y, *(p.p_data));
  }
};


#endif// POINT_H
