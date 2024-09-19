#include "utilities.h"

#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void do_something(const Print &printer) { printer("Snow"); }


void functors()
{
  Print print;
  print("Mahoro");
  do_something(print);
  fmt::println("{}", print("Daniel", "Gray"));
}

void Print::operator()(const std::string &name) const { fmt::println("The name is: {} ", name); }

std::string Print::operator()(const std::string &last_name, const std::string &first_name) const
{
  return (last_name + " " + first_name);
}