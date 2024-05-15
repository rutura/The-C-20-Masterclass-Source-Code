#ifndef OVAL_H
#define OVAL_H
#include "shape.h"
#include <string_view>
class Oval : public Shape
{
public:
  Oval() = default;
  Oval(double x_radius, double y_radius, std::string_view description);
  ~Oval();


  virtual void draw() const override
  {
    fmt::println(
      "Oval::draw() called. Drawing {} with m_x_radius : {} and m_y_radius :{}", m_description, m_x_radius, m_y_radius);
  }

  virtual void draw(int color_depth, std::string_view color) const
  {
    fmt::println("Drawing with color depth : {} and color : {}", color_depth, color);
  }

public:
  double get_x_rad() const { return m_x_radius; }

  double get_y_rad() const { return m_y_radius; }

private:
  double m_x_radius{ 0.0 };
  double m_y_radius{ 0.0 };
};

#endif// OVAL_H
