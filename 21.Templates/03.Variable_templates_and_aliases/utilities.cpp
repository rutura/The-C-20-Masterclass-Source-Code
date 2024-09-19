#include "utilities.h"

#include "template_aliases.h"
#include "variable_templates.h"

#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void variable_templates_demo()
{
  //Using function template
  fmt::println("Using function template");
  auto pi_float = variable_templates::pi<float>();
  auto pi_double = variable_templates::pi<double>();
  auto pi_long_double = variable_templates::pi<long double>();
  fmt::println("Pi: float: {}, double: {}, long double: {}", pi_float, pi_double, pi_long_double);

  //Using variable template
  fmt::println("Using variable template");
  auto pi_float_v = variable_templates::PI<float>;
  auto pi_double_v = variable_templates::PI<double>;
  auto pi_long_double_v = variable_templates::PI<long double>;
  fmt::println("Pi: float: {}, double: {}, long double: {}", pi_float_v, pi_double_v, pi_long_double_v);
}


void template_aliases_demo()
{
  //Using alias template
  fmt::println("Using alias template");
  template_aliases::Vec<int> vec{ 1, 2, 3, 4, 5 };
  for (const auto &elem : vec) { fmt::print("{} ", elem); }
  fmt::print("\n");

  template_aliases::StringKeyStore<int> store;
  store.insert("one", 1);
  store.insert("two", 2);
  store.insert("three", 3);
  fmt::println("Value of one: {}", store.get("one"));
  fmt::println("Value of two: {}", store.get("two"));
  fmt::println("Value of three: {}", store.get("three"));
}