#include "pure_virt_func_abstract_classes.h"

namespace pure_virt_func_abstract_classes {

//Implementation
Shape::Shape(std::string_view description)
  : m_description(description) {}


//Implementation
Rectangle::Rectangle(double width, double height, std::string_view description)
  : Shape(description), m_width(width), m_height(height) {}

//Implementation
Circle::Circle(double radius, std::string_view description)
  : Shape(description), m_radius(radius) {}


}