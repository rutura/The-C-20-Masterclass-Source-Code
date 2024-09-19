#pragma once

#include <fmt/format.h>
#include <string>


namespace polymorphism_with_static_members {

//Shape class
class Shape
{
public:
  Shape();
  Shape(std::string_view description);
  virtual ~Shape();
  void draw() const { fmt::println("Shape::draw() called for : {}", m_description); }

  virtual int get_count() const { return m_count; }

  static int m_count;

protected:
  std::string m_description;
};

//Ellipse class
class Ellipse : public Shape
{
public:
  Ellipse();
  Ellipse(double x_radius, double y_radius, std::string_view description);
  ~Ellipse();

  virtual int get_count() const override { return m_count; }

  static int m_count;

private:
  double m_x_radius;
  double m_y_radius;
};

}// namespace polymorphism_with_static_members