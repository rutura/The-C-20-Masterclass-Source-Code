#include "utilities.h"

#include "cylinder.h"
#include "person.h"
#include "point.h"
#include "square.h"

#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

//#1: Constructor default parameters
void constructor_default_parameters()
{
  Cylinder c1(4);
  fmt::println("volume : {}", c1.volume());
}


//#2: Constructor initializer lists
void constructor_initializer_lists()
{
  Cylinder c1(5);
  fmt::println("base_rad : {}", c1.get_base_radius());
  fmt::println("height : {}", c1.get_height());
  fmt::println("volume : {}", c1.volume());
}

// Is square1 > to square2 ? true or false
bool compare(const Square &square1, const Square &square2)
{
  return (square1.surface() > square2.surface()) ? true : false;
}


//#3: Explicit constructors
void explicit_constructors()
{

  Square s1(100.0);
  Square s2(20.0);

  //    fmt::println( "{}",fmt::ptr(std::boolalpha));
  fmt::println("s1 > s2 : {}", compare(s1, s2));// false

  Square s3(45.9);
  // Implicit conversions
  fmt::println("s1 > 45.9 : {}", compare(s1, s3));// false
}


// #4: Constructor delegation
void constructor_delegation() { Square s1(100.0); }

// #5: Copy constructors
void copy_constructors()
{
  Person p1("John", "Snow", 25);
  p1.print_info();

  // Create a person copy
  Person p2(p1);
  p2.print_info();

  fmt::println("-------");

  p1.set_age(30);
  p1.print_info();
  p2.print_info();
}

// #6: Arrays store copies
void arrays_store_copies()
{

  Person p1("John", "Snow", 25);
  Person p2("Sam", "Gray", 45);
  Person p3("Johny", "Drill", 5);
  p1.print_info();
  p2.print_info();
  p3.print_info();

  fmt::println("----");

  Person students[]{ p1, p2, p3 };
  for (size_t i{}; i < std::size(students); ++i) { students[i].print_info(); }

  fmt::println("----");
  for (Person &p : students) { p.print_info(); }
}

// #7: Move constructors
/*
void move_constructors(){
	// Point p1(10.4,15.6);
	// p1.print_info();

	// Create a copy from a temporary
	Point p3(std::move(Point(20.5, 5.8)));
	p3.print_info();
}
*/


// #8: Deleted constructors
void deleted_constructors()
{
  //Point p1(std::move(Point(4.6,5.2)));
  Point p1(4.6, 5.2);
}