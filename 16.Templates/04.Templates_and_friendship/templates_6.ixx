/*
  .#6: Class is template, friends are template, and we want any instance 
      of the friend templates to have access to private members of the class.
*/
module;

#include <fmt/format.h>

export module templates_6;
namespace templates_6 {

  //template <typename T>
  //class Canvas;

  export template <typename T>
  class Point {
    template <typename U>
    friend class Canvas;

    template <typename U>
    friend void print_point(const Point<U>& p);

    T x;
    T y;

  public:
    Point(T x, T y) : x(x), y(y) {}
  };

  export template <typename T>
  void print_point(const Point<T>& p) {
    fmt::print("Point: ({}, {})\n", p.x, p.y);
  }

  export template <typename T>
  class Canvas {
  public:
    void draw(const Point<T>& p) {
      fmt::print("Drawing point: ({}, {})\n", p.x, p.y);
    }
  };

}  // namespace templates_6
