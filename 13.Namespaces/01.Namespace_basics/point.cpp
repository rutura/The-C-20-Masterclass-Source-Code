#include "point.h"

#include <fmt/format.h>

//Implementations
namespace Geom {

Point::Point(double x, double y) : m_x{ x }, m_y{ y } {}

Point::Point() : Point(0.0, 0.0) {}
void Point::print_info() const { fmt::println("Point [ x: {}, y: {}]", m_x, m_y); }
Point::~Point() {}

}// namespace Geom