#include <fmt/format.h>

// internal linkage -> external linkage
extern const double distance{ 45.7 };

void print_distance();// Declaration
void some_other_function();// Declaration


int main()
{

  fmt::println("distance(main) : {}", distance);
  fmt::println("&distance(main) : {}", fmt::ptr(&distance));

  fmt::println("\n");
  print_distance();

  fmt::println("----");
  some_other_function();
  return 0;
}