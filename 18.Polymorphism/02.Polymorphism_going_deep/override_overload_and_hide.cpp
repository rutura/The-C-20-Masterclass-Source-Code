#include "override_overload_and_hide.h"

namespace override_overload_and_hide {
//Implementation
Shape::Shape(std::string_view description)
  : m_description(description) {}

Shape::~Shape() {}

//Implementation
Oval::Oval(double x_radius, double y_radius, std::string_view description)
  : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}

Oval::~Oval() {}


//Implementation
Circle::Circle(double radius, std::string_view description)
  : Oval(radius, radius, description) {}

Circle::~Circle() {}


}