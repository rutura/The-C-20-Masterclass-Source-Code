#include <fmt/format.h>

namespace {
double add(double a, double b);// Declaration
}


int main()
{

  double result = add(10.2, 20.2);
  fmt::println("result : {}", result);

  return 0;
}


namespace {
double add(double a, double b) { return a + b; }
}// namespace
