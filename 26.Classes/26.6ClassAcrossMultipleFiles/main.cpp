#include "cylinder.h"
#include <fmt/format.h>

int main()
{
  Cylinder cylinder1(10, 10);
  fmt::println("volume : {}", cylinder1.volume());

  return 0;
}