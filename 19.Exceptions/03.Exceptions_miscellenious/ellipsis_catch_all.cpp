#include "ellipsis_catch_all.h"

namespace ellipsis_catch_all {
void some_function(size_t i)
{
  if (i == 0) throw 1;
  if (i == 2) throw "const char*-Hello there";
  if (i == 3) throw CriticalError("Something is wrong");
  if (i == 4) throw std::string("std::string-Hello there");
}
}