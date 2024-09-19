#include "utilities.h"

#include "number.h"
#include "point.h"

#include <fmt/format.h>
#include <iostream>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }


double sum(double a, double b) { return a + b; }
void use_point(const Point &p) { std::cout << "Printing the point from use_point func: " << p << "\n"; }


void custom_type_conversions(){
	Number n1(22);
	Number n2(10);

	double result = sum(static_cast<double>(n1),static_cast<double>(n2));
	std::cout << "result: " << result << "\n";
	//use_point(static_cast<Point>(n1));
}


void implicit_conversions_for_overloaded_binary_operators()
{
  Number n1(22);

  auto n12 = (n1 + 2);
  //auto n21 = (2 + n1); // operator+ is done as a member. First operand can't use implicit conversions.
  auto n1_42 = 42 - n1;

  //std::cout << "n1: " << n1 << "\n";
  //std::cout << "n1 + 2: " << n12 << "\n";
  //std::cout << "2 + n1: " << n21 << "\n";
  //std::cout << "42 - n1: " << n1_42<< "\n";
}