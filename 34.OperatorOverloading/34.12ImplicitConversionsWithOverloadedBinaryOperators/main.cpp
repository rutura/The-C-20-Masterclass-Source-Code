#include "number.h"// Assuming Number class is defined in number.h
#include <fmt/format.h>


int main()
{
  Number n1(22);

  auto n12 = (n1 + 2);
  auto n21 = (2 + n1);
  auto n1_42 = 42 - n1;

  fmt::println("n1: {}", n1);
  fmt::println("n1 + 2: {}", n12);
  fmt::println("2 + n1: {}", n21);
  fmt::println("42 - n1: {}", n1_42);

  return 0;
}
