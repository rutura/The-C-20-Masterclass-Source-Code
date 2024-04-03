#include <fmt/format.h>


int main()
{

  int condition{ -5 };

  bool bool_condition = condition;


  if (bool_condition) {
    fmt::println("We have a {} in our variable", bool_condition);// different from 0
  } else {
    fmt::println("We have a {} in our variable", bool_condition);// zero
  }

  return 0;
}