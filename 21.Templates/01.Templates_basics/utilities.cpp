#include "utilities.h"

#include "class_template_basics.h"
#include "template_basics.h"
#include "template_member_functions.h"
#include "template_parameter_types.h"
#include "template_template_parameters.h"

#include <string_view>
#include <string>
#include <fmt/format.h>


void print_msg(std::string_view msg) { fmt::println("{}", msg); }


void function_template_basics_demo()
{

  auto value = template_basics::add(1, 2);
  fmt::print("The value is: {}\n", value);

  template_basics::Integer a(1);
  template_basics::Integer b(2);
  auto sum = a + b;
  fmt::print("The sum is: {}\n", sum.get());

  auto result = template_basics::add(11.1, 22.2);
  fmt::print("The result is: {}\n", result);

  std::string lastname = "Doe";
  std::string firstname = "John";
  auto fullname = template_basics::add(firstname, lastname);
  fmt::print("The full name is: {}\n", fullname);


  template_basics::Point p1(1.1, 2.2);
  template_basics::Point p2(3.3, 4.4);
  auto p3 = p1 + p2;
  fmt::print("The point is: ({}, {})\n", p3.get_x(), p3.get_y());

}

void class_template_basics_demo()
{

  //Points made up of int
  class_template_basics::Point<int> p1(1, 2);
  class_template_basics::Point<int> p2(3, 4);
  auto p3 = p1 + p2;
  fmt::print("The point is: ({}, {})\n", p3.get_x(), p3.get_y());


  //Points made up of double
  class_template_basics::Point<double> p4(1.1, 2.2);
  class_template_basics::Point<double> p5(3.3, 4.4);
  auto p6 = p4 + p5;
  fmt::print("The point is: ({}, {})\n", p6.get_x(), p6.get_y());

  //Custom integers
  class_template_basics::Point<template_basics::Integer> p7(template_basics::Integer(10), template_basics::Integer(20));
  class_template_basics::Point<template_basics::Integer> p8(template_basics::Integer(30), template_basics::Integer(40));
  auto p9 = p7 + p8;
  fmt::print("The point is: ({}, {})\n", p9.get_x().get(), p9.get_y().get());
}

void template_member_functions_demo()
{

  //Class is a template, member uses the class template parameter
  template_member_functions::Calculator_1<int> calc1;// Calls the default constructor
  auto result1 = calc1.add(1, 2);
  fmt::print("The result is: {}\n", result1);

  template_member_functions::Calculator_1<double> calc2;// Calls the default constructor
  auto result2 = calc2.multiply(1.1, 2.2);
  fmt::print("The result is: {}\n", result2);


  //Class is not a template, member is a function template
  template_member_functions::Calculator_2 calc3;// Calls the default constructor
  auto result3 = calc3.add(1, 2);
  fmt::print("The result is: {}\n", result3);

  auto result4 = calc3.multiply<double>(1.1, 2.2);
  fmt::print("The result is: {}\n", result4);


  //Both class and member are templates
  template_member_functions::Box<int> box1(10);
  auto result5 = box1.compare(10.1);
  fmt::print("The result is: {}\n", result5);

  //box1.compare(std::string("10"));	//Error. Can't compare int with string
  //fmt::print("The result is: {}\n", result5);
}

void template_parameter_types_demo()
{

  //class template
  template_parameter_types::Point<int> p1(1, 2);
  template_parameter_types::Point<int> p2(3, 4);
  auto p3 = p1 + p2;
  fmt::print("The point is: ({}, {})\n", p3.get_x(), p3.get_y());

  //function template
  auto result1 = template_parameter_types::maximum(11, 2);
  fmt::print("The result is: {}\n", result1);

  //Defaults
  auto result2 = template_parameter_types::add(11, 2);
  fmt::print("The result is: {}\n", result2);

  //Non-type template parameters
  template_parameter_types::Array<10> arr1;
  fmt::print("The size is: {}\n", arr1.get_size());
}

void template_template_parameters_demo()
{

  template_template_parameters::Container<int> container1;
  template_template_parameters::Processor<template_template_parameters::Container, int> processor1;
  processor1.process(container1, 1);
  processor1.process(container1, 2);
  processor1.process(container1, 3);

  /*
  template_template_parameters::Container<std::string> container2;
  template_template_parameters::Processor<template_template_parameters::Container, std::string> processor2;
  processor2.process(container2, "Hello");
  */
}