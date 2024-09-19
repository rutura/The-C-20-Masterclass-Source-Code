#include "utilities.h"

#include "point.h"
#include "scores.h"

#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

//#1: Overloading the + operator as a member
/*
void overload_plus_operator_as_member()
{
  Point p1(10, 10);
  Point p2(20, 20);
  Point p3{ p1 + p2 };// p1.operator+(p2)

  Point p4{ p2 + Point(5, 5) };

  p3.print_info();
  p4.print_info();

  (Point(20, 20) + Point(10, 10)).print_info();
}
*/


//#2: Overload operator+ as a non member
/*void overload_plus_operator_as_non_member()
{
  Point p1(10, 10);
  Point p2(20, 20);
  // Point p3{p1 + p2}; // opearator+(p1,p2);
  Point p3{ operator+(p1, p2) };

  Point p4{ p2 + Point(5, 5) };

  p3.print_info();
  p4.print_info();

  (Point(20, 20) + Point(10, 10)).print_info();
}*/


//#3: Overload the subscript operator
/*
void overload_subscript_operator()
{
  Point p1(10, 20);
  fmt::println("p1.x : {}", p1[0]);// x coordinate : 10
  fmt::println("p1.x : {}", p1.operator[](0));// x coordinate : 10
  fmt::println("p1.y : {}", p1[1]);// y coordinate : 20
}
*/

//#4: Overload the subscript operator for reading and writting
/*void overload_subscript_reading_writing()
{
  Point p1(10, 20);

  p1.print_info();

  // Changing the data
  p1[0] = 35.6;
  p1[1] = 23.9;

  p1.print_info();
}*/


//#5: Subscript operator for collection types
void overload_subscript_operator_for_collection_types()
{
  Scores math("Math");
  math.print_info();

  for (size_t i{}; i < 20; ++i) { if (i == 0) { math[0] = 73.7; } else { math[i] = math[i - 1] + 0.56; } }

  math.print_info();

  fmt::println("------");


  // Const objecst
  const Scores geo("Geography");
  fmt::println("geo [5] : {}", geo[5]);

}