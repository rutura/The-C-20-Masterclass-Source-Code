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


//Implementations
namespace Geom {

Point::Point(double x, double y) : m_x{ x }, m_y{ y } {}

Point::Point() : Point(0.0, 0.0) {}

Point::~Point() {}

}// namespace Geom