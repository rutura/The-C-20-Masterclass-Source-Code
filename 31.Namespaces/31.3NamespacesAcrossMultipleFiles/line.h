#ifndef LINE_H
#define LINE_H

#include "point.h"

namespace Geom {

class Line
{
public:
  Line(const Point &start, const Point &end);

  void print_info() const
  {
    fmt::println("Line from ");
    m_start.print_info();
    fmt::println("to : ");
    m_end.print_info();
  }

private:
  Point m_start;
  Point m_end;
};

}// namespace Geom


#endif// LINE_H
