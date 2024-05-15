#ifndef SHAPE_H
#define SHAPE_H
#include <fmt/format.h>
#include <string>
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

#endif// SHAPE_H
