#include "utilities.h"

#include "point.h"
#include "car.h"
#include <iostream>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }


void copy_constructor()
{

  Point p1(10, 10, 10);
  Point p2(20, 20, 20);
  Point p77(3, 3, 3);

  std::cout << "p1 : " << p1 << "\n";
  std::cout << "p2 : " << p2 << "\n";
  std::cout << "-----\n";

  // Assignment
  // p1 = p2 = p77;
  // p1.operator=(p2).operator=(p77);
  p1.operator=(p2.operator=(p77));

  std::cout << "p1 : " << p1 << "\n";
  std::cout << "p2 : " << p2 << "\n";

  // Change data
  p1.set_data(55);

  std::cout << "-----------\n";
  std::cout << "p1 : " << p1 << "\n";
  std::cout << "p2 : " << p2 << "\n";

  /*
  Point p3(30,30,30);
  Point p4 = p3;

  std::cout << "p3 : " << p3 << "\n";
  std::cout << "p4 : " << p4 << "\n";

  p3.set_data(77);

  std::cout << "-----\n";
  std::cout << "p3 : " << p3 << "\n";
  std::cout << "p4 : " << p4 << "\n";

  std::cout << "Done!\n";
  */
}

void copy_constructor_from_other_types()
{
  Point p1(10, 10, 10);
  Car c1("red", 200.0);

  p1 = c1;

  // fmt::println("p1 : {}", p1);// requires that you have defined fmt::formatter for Point
  std::cout << "p1 : " << p1 << "\n";
}