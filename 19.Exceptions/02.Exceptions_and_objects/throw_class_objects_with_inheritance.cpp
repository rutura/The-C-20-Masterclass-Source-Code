#include "throw_class_objects_with_inheritance.h"


namespace throw_class_objects_with_inheritance {
void do_something(size_t i)
{
  if (i == 2) { throw CriticalError("i is 2"); }

  if (i == 3) { throw SmallError("i is 3"); }

  if (i == 4) { throw Warning("i is 4"); }
  fmt::println("Doing something at iteration : {}", i);
}
}