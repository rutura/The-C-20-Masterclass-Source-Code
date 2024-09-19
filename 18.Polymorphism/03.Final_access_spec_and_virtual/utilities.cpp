#include "utilities.h"
#include "final_override_not_keywords.h"
#include "no_poly_and_acc_spec.h"
#include "poly_func_and_acc_spec.h"
#include "virt_func_default_arg.h"

#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }


void final_keyword_demo() { fmt::println("Can't inherit from a final class"); }

void final_override_not_keywords_demo() { final_override_not_keywords::override(); }

void poly_func_and_acc_spec_demo()
{

  // Accessing stuff through the base class pointer
  std::shared_ptr<poly_func_and_acc_spec::Shape> shape0 =
    std::make_shared<poly_func_and_acc_spec::Ellipse>(1, 5, "ellipse0");
  shape0->draw();// Polymorphism
  // shape0->func(); // Error :  func is private in Shape

  fmt::println("------------");

  // Direct objects : static binding
  poly_func_and_acc_spec::Ellipse ellipse1(1, 6, "ellipse1");
  ellipse1.func();// Works
  // ellipse1.draw(); //Error : draw() is private in Ellipse.- Static binding


  fmt::println("------------");

  // Raw derived object assigned to raw base object
  // Slicing will occur, Shape::draw will be called
  poly_func_and_acc_spec::Shape shape3 = poly_func_and_acc_spec::Ellipse(2, 3, "ellipse3");
  shape3.draw();// Shape::draw() called
  // shape3.func(); // Error : func is private in shape
}

void non_polymorphic_func_and_acc_spec_demo()
{

  // Accessing stuff through the base class pointer
  std::shared_ptr<no_poly_and_acc_spec::Shape> shape0 =
    std::make_shared<no_poly_and_acc_spec::Ellipse>(1, 5, "ellipse0");
  shape0->draw();// Static binding
  // shape0->func(); // Error :  func is private in Shape

  fmt::println("------------");

  // Direct objects : static binding
  no_poly_and_acc_spec::Ellipse ellipse1(1, 6, "ellipse1");
  ellipse1.func();// Works
  // ellipse1.draw(); //Error : draw() is private in Ellipse.- Static binding


  fmt::println("------------");

  // Raw derived object assigned to raw base object
  // Slicing will occur, Shape::draw will be called
  no_poly_and_acc_spec::Shape shape3 = no_poly_and_acc_spec::Ellipse(2, 3, "ellipse3");
  shape3.draw();// Shape::draw() called
  // shape3.func(); // Error : func is private in shape
}


void virt_func_default_arg_demo()
{

  // Base ptr : Uses polymorphism
  virt_func_default_arg::Base *base_ptr1 = new virt_func_default_arg::Derived;
  double result = base_ptr1->add();
  fmt::println("Result (base ptr) : {}", result);// 12


  fmt::println("---------------------");

  // Base ref : Uses Polymorphism
  virt_func_default_arg::Derived derived1;
  virt_func_default_arg::Base &base_ref1 = derived1;
  result = base_ref1.add();
  fmt::println("Result (base ref) : {}", result);// 12

  fmt::println("---------------------");


  // Raw objects
  virt_func_default_arg::Base base3;
  result = base3.add();
  fmt::println("raw result : {}", result);

  fmt::println("---------------------");

  // Direct object : Uses static binding
  virt_func_default_arg::Derived derived2;
  result = derived2.add();
  fmt::println("Result (Direct object) : {}", result);// 22

  fmt::println("---------------------");

  // Raw objects - slicing : uses static binding
  virt_func_default_arg::Base base1 = derived2;
  result = base1.add();
  fmt::println("Result (Raw objects assignment) : {}", result);// 11
}