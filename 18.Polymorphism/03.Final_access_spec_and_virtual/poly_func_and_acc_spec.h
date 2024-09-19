#pragma once

#include <fmt/format.h>
#include <string>


namespace poly_func_and_acc_spec {

//Shape class
class Shape
{
public:
  Shape();
  Shape(std::string_view description);
  ~Shape();

public:
  virtual void draw() const { fmt::println("Shape::draw() called for : {}", m_description); }

private:
  // Can be inherited even if it is private. Derived class will put
  // this in public scope
  virtual void func() const { fmt::println("Shape::func() called for : {}", m_description); }

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
  virtual void draw() const override { fmt::println("Ellipse::draw() called for : {}", m_description); }

public:
  virtual void func() const override { fmt::println("Ellipse::func() called for : {}", m_description); }

private:
  double m_x_radius;
  double m_y_radius;
};
}//namespace poly_func_and_acc_spec