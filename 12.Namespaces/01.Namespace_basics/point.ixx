module;

#include <fmt/format.h>

export module point;


namespace Geom {

export class Point
{
  public:
    Point();
    Point(double x, double y);
    void print_info() const { fmt::println("Point [ x: {}, y: {}]", m_x, m_y); }
    ~Point();

  private:
    double m_x;
    double m_y;
};

}// namespace Geom