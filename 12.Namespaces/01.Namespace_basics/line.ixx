module;

#include <fmt/format.h>

import point;

export module line;

namespace Geom {

export class Line
{
public:
  Line(const Point &start, const Point &end);

  void print_info() const
  {
    /*
    fmt::println("Line from ");
    m_start.print_info();
    fmt::println("to : ");
    m_end.print_info();
    */
  }

private:
  Point m_start;
  Point m_end;
};

}// namespace Geom