#include "nested_namespaces.h"

namespace Hello {
namespace World {
  void say_something()
  {
    fmt::println("Hello there ");
    fmt::println("The age is : {}", age);
  }
}
void do_something()
{
  // Here we don't have direct access to local_var, we have to go
  // through the namespace.
  fmt::println("Using local_var : {}", World::local_var);
}
}