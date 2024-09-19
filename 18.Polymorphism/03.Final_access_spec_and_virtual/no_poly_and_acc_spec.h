#pragma once

#include <fmt/format.h>
#include <string>

namespace no_poly_and_acc_spec {

//Shape class
class Shape
{
public:
  Shape();
  Shape(std::string_view description);
  ~Shape();

public:
  void draw() const { fmt::println("Shape::draw() called for : {}", m_description); }

private:
  void func() const { fmt::println("Shape::func() called for : {}", m_description); }

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

private:
  void draw() const { fmt::println("Ellipse::draw() called for : {}", m_description); }

public:
  void func() const { fmt::println("Ellipse::func() called for : {}", m_description); }

private:
  double m_x_radius;
  double m_y_radius;
};


}// namespace no_poly_and_acc_spec