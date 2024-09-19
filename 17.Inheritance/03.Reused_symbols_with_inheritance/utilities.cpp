#include "utilities.h"

#include "reused_symbols.h"

#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void reused_symbols_demo()
{
  reused_symbols::Child child(33);
  child.print_var();// Calls the method in Child
  child.Parent::print_var();// Calls the method in Parent,
  // value in parent just contains junk or whatever
  // in class initialization we did.

  fmt::println("--------");
  child.show_values();
}