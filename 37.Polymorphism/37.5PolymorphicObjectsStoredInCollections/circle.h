#ifndef CIRCLE_H
#define CIRCLE_H
#include "oval.h"

class Circle : public Oval
{
public:
  Circle() = default;
  Circle(double radius, std::string_view description);
  ~Circle();

  virtual void draw() const
  {
    fmt::println("Circle::draw() called. Drawing {} with radius :{} ", m_description, get_x_rad());
  }
};

#endif// CIRCLE_H
