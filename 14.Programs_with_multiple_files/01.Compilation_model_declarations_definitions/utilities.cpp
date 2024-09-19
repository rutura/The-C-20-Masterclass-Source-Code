#include "utilities.h"
#include "person.h"
#include "point.h"

#include <iostream>

//Declarations
double weight;

// Functions :  defintion
double add(double a, double b) { return a + b; }


void use_point()
{
  Point p(10, 10);
  auto distance = p.distance_from_origin();
  std::cout << "distance: " << distance << "\n";
}

void use_person()
{
  weight = 5;// Assignment

  std::cout << weight << "\n";

  double result = add(10, 20.5);
  std::cout << "result: " << result << "\n";

  Person p1("John Snow", 27);
  p1.print_info();
}