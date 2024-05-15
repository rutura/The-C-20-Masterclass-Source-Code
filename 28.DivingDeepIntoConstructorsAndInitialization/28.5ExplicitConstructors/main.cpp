#include "square.h"
#include <fmt/format.h>

// Is square1 > to square2 ? true or false
bool compare(const Square &square1, const Square &square2)
{
  return (square1.surface() > square2.surface()) ? true : false;
}

int main()
{

  Square s1(100.0);
  Square s2(20.0);

  //    fmt::println( "{}",fmt::ptr(std::boolalpha));
  fmt::println("s1 > s2 : {}", compare(s1, s2));// false

  Square s3(45.9);
  // Implicit conversions
  fmt::println("s1 > 45.9 : {}", compare(s1, s3));// false


  return 0;
}