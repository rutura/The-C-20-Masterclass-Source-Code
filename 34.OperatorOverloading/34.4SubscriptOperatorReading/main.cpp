#include "point.h"
#include <fmt/format.h>


int main()
{

  Point p1(10, 20);

  //    fmt::println( "p1.x : {}" , p1[0] ); // x coordinate : 10
  fmt::println("p1.x : {}", p1.operator[](0));// x coordinate : 10
  fmt::println("p1.y : {}", p1[1]);// y coordinate : 20
  return 0;
}