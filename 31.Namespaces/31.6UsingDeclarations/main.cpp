#include "cylinder.h"
#include "line.h"
#include "operations.h"
#include "point.h"
#include <fmt/format.h>


// using Geom::Point; // Just bringing in the name from the namespace
using namespace Geom;


double add(double a, double b)
{
  fmt::println("::add");
  return a + b + 0.555;
}


// using Math::add;
// using namespace Math;

int main()
{

  Point p1(10, 20);
  Point p2(3.4, 6.1);
  p1.print_info();
  p2.print_info();

  fmt::println("---");

  Line l1(p1, p2);
  l1.print_info();

  fmt::println("---");

  Cylinder c1(1.4, 10);
  fmt::println("c1.volume : {}", c1.volume());

  fmt::println("---");

  Math_Weighted::add(10, 20);

  fmt::println("---");

  // using std::cout;
  /// using std::endl;
  using namespace std;// NOT RECOMMENDED!


  fmt::println("Hello World");


  return 0;
}