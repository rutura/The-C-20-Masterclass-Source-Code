#include "cylinder.h"
#include <fmt/format.h>


int main()
{

  Cylinder c1(4);
  fmt::println("volume : {}", c1.volume());

  return 0;
}