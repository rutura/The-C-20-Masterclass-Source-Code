#ifndef POINT_H
#define POINT_H
#include <fmt/format.h>

class Point
{
  friend std::ostream &operator<<(std::ostream &out, const Point &p);
  friend struct fmt::formatter<Point>;
  friend bool operator>(const Point &left, const Point &right);
  friend bool operator>=(const Point &left, const Point &right);
  friend bool operator==(const Point &left, const Point &right);
  friend bool operator!=(const Point &left, const Point &right);
  friend bool operator<(const Point &left, const Point &right);
  friend bool operator<=(const Point &left, const Point &right);

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;
  // Operators
  /*
  bool operator> (const Point& other) const;
  bool operator< (const Point& other) const;
  bool operator>=(const Point& other) const;
  bool operator<=(const Point& other) const;
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
  */
  double length() const;// Function to calculate distance from the point(0,0)
private:
  double m_x{};
  double m_y{};
};

/*
 - How to print Point obj on fmt stream
 - Reference: https://fmt.dev/latest/api.html
 */
template<> struct fmt::formatter<Point>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Point &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Point [x: {}, y: {}, length: {}]", obj.m_x, obj.m_y, obj.length());
  }
};
inline std::ostream &operator<<(std::ostream &out, const Point &p)
{
  out << "Point [ x : " << p.m_x << ", y : " << p.m_y << " length : " << p.length() << "]";
  return out;
}

inline bool operator>(const Point &left, const Point &right) { return (left.length() > right.length()); }

inline bool operator>=(const Point &left, const Point &right) { return (left.length() >= right.length()); }

inline bool operator==(const Point &left, const Point &right) { return (left.length() == right.length()); }

inline bool operator!=(const Point &left, const Point &right) { return (left.length() != right.length()); }

inline bool operator<(const Point &left, const Point &right) { return (left.length() < right.length()); }

inline bool operator<=(const Point &left, const Point &right) { return (left.length() <= right.length()); }


#endif// POINT_H
