import math_stuff;
#include <fmt/format.h>

int main()
{
  auto result = add(10, 20);
  fmt::println("result : {}", result);

  greet("John");

  print_name_length("John");

  Point point1(22, 44);
  fmt::println("point1 : {}", point1);
}
