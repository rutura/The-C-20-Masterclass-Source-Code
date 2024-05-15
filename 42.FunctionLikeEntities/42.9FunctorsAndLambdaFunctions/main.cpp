#include <fmt/format.h>

int main()
{

  int result = [](int x, int y) -> int { return x + y; }(7, 3);
  fmt::println("{}", result);


  // Auto type deduction can help deduce the type of the generated lambda function
  // We don't have access to that in our C++ code.
  auto func = [](int x, int y) -> int { return x + y; };
  result = func(10, 20);
  fmt::println("{}", result);

  return 0;
}