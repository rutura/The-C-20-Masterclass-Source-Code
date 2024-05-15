#include "cylinder.h"
#include <fmt/format.h>


int main()
{
  Cylinder cylinder1(3.3, 10.0);
  fmt::println("Volume of cylinder : {}", cylinder1.volume());
  fmt::println("Cylinder default color : {}", Cylinder::default_color);
  fmt::println("Cylinder default color : {}", cylinder1.default_color);

  return 0;
}