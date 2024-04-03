import <iostream>;
#include <fmt/format.h>;

import math_stuff;

int main()
{
  auto result = add(10, 20);
  fmt::println("result: {}", result);

  greet("John");

  print_name_length("John");
}