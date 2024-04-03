#ifndef POINT_H
#define POINT_H
#include <fmt/format.h>
#include <iostream>


class Point
{
  friend std::ostream &operator<<(std::ostream &os, const Point &p);
  friend std::istream &operator>>(std::istream &is, Point &p);
  friend struct fmt::formatter<Point>;

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;

  /*
  std::ostream& operator<< (std::ostream& os){
          os << "Point [ x : " << m_x << ", y : " << m_y << "]";
          return os;
  }
  */

private:
  double length() const;// Function to calculate distance from the point(0,0)

private:
  double m_x{};
  double m_y{};
};

inline std::ostream &operator<<(std::ostream &os, const Point &p)
{
  os << "Point [ x : " << p.m_x << ", y : " << p.m_y << "]";
  return os;
}

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

template<> struct fmt::formatter<Point>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Point &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Point [x: {}, y: {}]", obj.m_x, obj.m_y);
  }
};
#endif// POINT_H
