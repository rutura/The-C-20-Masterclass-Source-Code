#include <fmt/format.h>
extern const double distance;// Declaration

void print_distance()
{
  //++distance; // Error : can't modify a read only variable.
  fmt::println("distance(some_other_file) : {}", distance);
  fmt::println("&distance(some_other_file) : {}", fmt::ptr(&distance));
}

// External linkage -> internal linkage
void some_other_function() { fmt::println("Hello there"); }
// Internal linkage
namespace {
void some_other_function() { fmt::println("Hello there"); }
}// namespace