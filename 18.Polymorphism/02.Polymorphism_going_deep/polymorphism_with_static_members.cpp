#include "polymorphism_with_static_members.h"


namespace polymorphism_with_static_members {
//Implementation
int Shape::m_count{ 0 };

Shape::Shape(std::string_view description)
  : m_description(description) { ++m_count; }

Shape::Shape()
  : Shape("NoDescription") {}

Shape::~Shape() { --m_count; }


//Implementation
int Ellipse::m_count{ 0 };

Ellipse::Ellipse(double x_radius, double y_radius, std::string_view description)
  : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) { ++m_count; }

Ellipse::Ellipse()
  : Ellipse(0.0, 0.0, "NoDescription") {}

Ellipse::~Ellipse() { --m_count; }


}