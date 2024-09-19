#include "sizes_and_slicing.h"

namespace sizes_and_slicing {
//Implementations
Shape::Shape(std::string_view description)
  : m_description(description) {}

Shape::~Shape() {}


//Implementations
Oval::Oval(double x_radius, double y_radius, std::string_view description)
  : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}

Oval::~Oval() {}

//Implementations
Circle::Circle(double radius, std::string_view description)
  : Oval(radius, radius, description) {}

Circle::~Circle() {}


}