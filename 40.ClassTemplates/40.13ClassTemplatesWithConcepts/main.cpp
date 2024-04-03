#include "boxcontainer.h"

template<typename T> requires std::is_arithmetic_v<T> class Point
{
  /*
      static_assert(std::is_arithmetic_v<T>,
  "Coordinates of Point can only be numbers.");
          */
  friend struct fmt::formatter<Point>;

public:
  Point() = default;
  Point(T x, T y) : m_x(x), m_y(y) {}
  friend std::ostream &operator<<(std::ostream &out, const Point<T> operand)
  {
    out << "Point [ x : " << operand.m_x << ", y : " << operand.m_y << "]";
    return out;
  }

private:
  T m_x;
  T m_y;
};

template<typename T> struct fmt::formatter<Point<T>>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Point<T> &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Point [ x: {}, y: {}]", obj.m_x, obj.m_y);
  }
};


int main()
{


  Point<int> point_int(10, 20);
  fmt::println("point_int : {}", point_int);

  Point<double> point_double(11.1, 12.2);
  fmt::println("point_double : {}", point_double);


  // Point<std::string> point_string("Hello","World");
  // fmt::println("point_string : {}" , point_string );


  BoxContainer<Point<int>> point_box;
  point_box.add(point_int);
  point_box.add(Point<int>(40, 50));

  fmt::println("point_box : {}", point_box);


  return 0;
}