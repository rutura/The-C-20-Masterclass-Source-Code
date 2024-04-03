#include "utilities.h"
#include <fmt/format.h>

int main()
{

  double result = add(10.5, 20.8);
  fmt::println("result : {}", result);

  return 0;
}