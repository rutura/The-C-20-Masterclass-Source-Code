#include "utilities.h"

#include "override_keyword.h"
#include "override_overload_and_hide.h"
#include "polymorphism_diff_levels.h"
#include "polymorphism_with_static_members.h"

#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }


void override_keyword_demo()
{

  override_keyword::Circle circle1(7.2, "circle1");
  override_keyword::Oval oval1(13.3, 1.2, "Oval1");
  override_keyword::Circle circle2(11.2, "circle2");
  override_keyword::Oval oval2(31.3, 15.2, "Oval2");
  override_keyword::Circle circle3(12.2, "circle3");
  override_keyword::Oval oval3(53.3, 9.2, "Oval3");

  // Raw pointers
  override_keyword::Shape *shapes3[]{ &circle1, &oval1, &circle2, &oval2, &circle3, &oval3 };

  for (override_keyword::Shape *shape_ptr : shapes3) { shape_ptr->draw(); }
}


void overloading_overriding_and_hiding_demo()
{

  override_overload_and_hide::Shape *shape_ptr = new override_overload_and_hide::Circle(10, "Circle1");
  // shape_ptr->draw(45,"Red");
  shape_ptr->draw(45);

  delete shape_ptr;
}

void polymorphism_diff_levels_demo()
{

  // Animal polymorphism
  polymorphism_diff_levels::Dog dog1("dark gray", "dog1");
  polymorphism_diff_levels::Cat cat1("black stripes", "cat1");
  polymorphism_diff_levels::Pigeon pigeon1("white", "pigeon1");
  polymorphism_diff_levels::Crow crow1("black", "crow1");

  polymorphism_diff_levels::Animal *animals[]{ &dog1, &cat1, &pigeon1, &crow1 };

  for (const auto &animal : animals) { animal->breathe(); }

  fmt::println("------------");

  // Feline polymorphism
  polymorphism_diff_levels::Dog dog2("dark gray", "dog2");
  polymorphism_diff_levels::Cat cat2("black stripes", "cat2");
  polymorphism_diff_levels::Pigeon pigeon2("white", "pigeon2");
  // Putting pigeon in felines will result in compiler error
  //  pigeon is and Animal,a but is not a feline.
  polymorphism_diff_levels::Animal animal1("some animal");

  polymorphism_diff_levels::Feline *felines[]{ &dog2, &cat2 };

  for (const auto &feline : felines) { feline->run(); }


  fmt::println("------------");

  // Bird polymorphism
  polymorphism_diff_levels::Pigeon pigeon3("white", "pigeon1");
  polymorphism_diff_levels::Crow crow3("black", "crow1");

  polymorphism_diff_levels::Bird *birds[]{ &pigeon3, &crow3 };

  for (const auto &bird : birds) { bird->fly(); }
}

void polymorphism_with_static_members_demo()
{

  // Shape
  polymorphism_with_static_members::Shape shape1("shape1");
  fmt::println("shape count : {}", polymorphism_with_static_members::Shape::m_count);// 1

  polymorphism_with_static_members::Shape shape2("shape2");
  fmt::println("shape count : {}", polymorphism_with_static_members::Shape::m_count);// 2

  polymorphism_with_static_members::Shape shape3;
  fmt::println("shape count : {}", polymorphism_with_static_members::Shape::m_count);// 3

  fmt::println("***********************************************");

  // Ellipse
  polymorphism_with_static_members::Ellipse ellipse1(10, 12, "ellipse1");
  fmt::println("shape count : {}", polymorphism_with_static_members::Shape::m_count);// 4
  fmt::println("ellipse count : {}", polymorphism_with_static_members::Ellipse::m_count);// 1


  fmt::println("***********************************************");

  // Shape polymorphism

  polymorphism_with_static_members::Shape *shapes[]{ &shape1, &ellipse1 };
  for (auto &s : shapes) { fmt::println("count : {}", s->get_count()); }
}