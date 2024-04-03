#include "ellipse.h"


int main()
{

  // Shape
  Shape shape1("shape1");
  fmt::println("shape count : {}", Shape::m_count);// 1

  Shape shape2("shape2");
  fmt::println("shape count : {}", Shape::m_count);// 2

  Shape shape3;
  fmt::println("shape count : {}", Shape::m_count);// 3

  fmt::println("***********************************************");

  // Ellipse
  Ellipse ellipse1(10, 12, "ellipse1");
  fmt::println("shape count : {}", Shape::m_count);// 4
  fmt::println("ellipse count : {}", Ellipse::m_count);// 1


  fmt::println("***********************************************");

  // Shape polymorphism

  Shape *shapes[]{ &shape1, &ellipse1 };
  for (auto &s : shapes) { fmt::println("count : {}", s->get_count()); }

  return 0;
}