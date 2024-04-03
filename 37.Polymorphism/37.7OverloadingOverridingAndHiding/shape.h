#ifndef SHAPE_H
#define SHAPE_H

#include <fmt/format.h>
#include <string>
#include <string_view>
class Shape
{
public:
  Shape() = default;
  Shape(std::string_view description);
  ~Shape();

  virtual void draw() const { fmt::println("Shape::draw() called. Drawing {}", m_description); }

  virtual void draw(int color_depth) const { fmt::println("Shape::Drawing with color depth : {}", color_depth); }

protected:
  std::string m_description{ "" };
};

#endif// SHAPE_H
