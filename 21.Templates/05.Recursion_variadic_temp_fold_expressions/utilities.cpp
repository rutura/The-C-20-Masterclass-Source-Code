#include "utilities.h""

#include "fold_expressions.h"
#include "recursion.h"
#include "variadic_class_templates.h"
#include "variadic_function_templates.h"

#include <fmt/format.h>


void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void recursion_demo()
{
  fmt::println("Factorial of 5 using bare recursion: {}", recursion::factorial_bare(5));
  fmt::println("Factorial of 5 using template recursion: {}", recursion::Factorial<5>::value);
  fmt::println("Factorial of 5 using constexpr function: {}", recursion::factorial(5));
}


void variadic_function_templates_demo()
{
  //Do the sums from 1 element up to 5 elements
  //auto value = variadic_function_templates::add(1);	//This will not compile,we need at least two parameters.
  fmt::println("Sum of 2 elements: {}", variadic_function_templates::add(1, 2));
  fmt::println("Sum of 3 elements: {}", variadic_function_templates::add(1, 2, 3));
  fmt::println("Sum of 4 elements: {}", variadic_function_templates::add(1, 2, 3, 4));
  fmt::println("Sum of 5 elements: {}", variadic_function_templates::add(1, 2, 3, 4, 5));
  fmt::println("Sum of 5 elements using add2: {}", variadic_function_templates::add2(1, 2, 3, 4, 5));
}

void variadic_class_templates_demo()
{

  // Creating a MyTuple with different types
  variadic_class_templates::MyTuple<int, std::string, double> myTuple(42, "Hello", 3.14);

  // Accessing the first value
  fmt::println("First: {}", myTuple.getValue());

  // Casting to the base class to access the next value
  variadic_class_templates::MyTuple<std::string, double> &rest = myTuple;
  fmt::println("Second: {}", rest.getValue());

  // Casting again to access the last value
  variadic_class_templates::MyTuple<double> &last = rest;
  fmt::println("Third: {}", last.getValue());


  //Create a tuple with 3 elements
  /*
  variadic_class_templates::MyTuple<int, double, std::string> tuple(1, 3.14, "Hello");
  fmt::println("First element: {}", tuple.getValue());
  fmt::println("Second element: {}", static_cast<variadic_class_templates::MyTuple<double, std::string>&>(tuple).getValue());
  fmt::println("Third element: {}", static_cast<variadic_class_templates::MyTuple<std::string>&>(tuple).getValue());
  */
}


void fold_expressions_demo()
{
  //Trying out fold expressions
  //Unary left fold
  fmt::println("Unary left fold add 1,2,3: {}", fold_expressions::add_unary_left_fold(1, 2, 3));
  fmt::println("Unary left fold sub 1,2,3: {}", fold_expressions::sub_unary_left_fold(1, 2, 3));

  //Unary right fold
  fmt::println("Unary right fold add 1,2,3: {}", fold_expressions::add_unary_right_fold(1, 2, 3));
  fmt::println("Unary right fold sub 1,2,3: {}", fold_expressions::sub_unary_right_fold(1, 2, 3));

  //Binary left fold
  fmt::println("Binary left fold add 1,2,3: {}", fold_expressions::add_binary_left_fold(1, 2, 3));
  fmt::println("Binary left fold sub 1,2,3: {}", fold_expressions::sub_binary_left_fold(1, 2, 3));

  //Binary right fold
  fmt::println("Binary right fold add 1,2,3: {}", fold_expressions::add_binary_right_fold(1, 2, 3));
  fmt::println("Binary right fold sub 1,2,3: {}", fold_expressions::sub_binary_right_fold(1, 2, 3));


  //Trying out empty parameter packs
  //Unary folds must have at least one parameter, otherwise, you'll get a compiler error.
  //fmt::println("Unary left fold add: {}", fold_expressions::add_unary_left_fold()); Error
  //fmt::println("Unary right fold add: {}", fold_expressions::add_unary_right_fold()); Error
  //fmt::println("Binary left fold add: {}", fold_expressions::add_binary_left_fold());
  //fmt::println("Binary right fold add: {}", fold_expressions::add_binary_right_fold());
  //fmt::println("Unary left fold add 1: {}", fold_expressions::add_unary_left_fold(1));
}