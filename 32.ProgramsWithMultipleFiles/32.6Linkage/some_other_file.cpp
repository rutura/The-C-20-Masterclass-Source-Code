#include <fmt/format.h>

const double distance{};// Declaration and definition

extern int item_count;// Declaration of some variable defined in some
                      // other translation unit


// Functions have external linkage by default
void print_distance()
{
  fmt::println("distance (other_file) : {}{}{}", distance, " &distance  :", fmt::ptr(&distance));
}

void print_item_count()
{
  fmt::println("item_count(other_file) : {}{}{}", item_count, " &item_count : ", fmt::ptr(&item_count));
}
