#include "square.h"
#include <fmt/format.h>

Square::Square(double side_param) : Square{ side_param, "black", 6 }
{
  m_position = 45.8;
  fmt::println("One param constructor called");
}

Square::Square(double side_param, const std::string &color_param, int shading_param)
  : m_side{ side_param }, m_color{ color_param }, m_shading{ shading_param }
{
  fmt::println("Three param constructor called");
}

double Square::surface() const { return m_side * m_side; }

Square::~Square() { fmt::println("Square object destroyed"); }
