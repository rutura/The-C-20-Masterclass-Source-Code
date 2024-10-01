module;

#include <fmt/format.h>

export module default_global_namespace;

// Global namespace
export double add(double a, double b) { return a + b; }

namespace My_Thing {

  export double add(double a, double b) { return a + b - 1; }

  export void do_something()
  {
    double result = ::add(5, 6);
    fmt::println("result : {}", result);
  }

}// namespace My_Thing
