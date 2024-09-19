#include "throw_class_objects.h"

namespace throw_class_objects {
void do_something(size_t i)
{
  if (i == 2) { throw SomethingIsWrong("i is 2"); }
  fmt::println("Doing something at iteration : {}", i);
}
}