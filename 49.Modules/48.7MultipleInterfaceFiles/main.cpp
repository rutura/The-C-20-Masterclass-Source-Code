// import <iostream>;
#include <fmt/format.h>
import math_stuff;
import print;

int main()
{
  auto result = add(10, 20);
  fmt::println("result : {}", result);
  // std::cout << "result : " << result << std::endl;

  greet();

  print_name_length("John");

  Point point1(22, 44);
  fmt::println("point1 : {}", point1);
  // std::cout << "point1 : " << point1 << std::endl;
}