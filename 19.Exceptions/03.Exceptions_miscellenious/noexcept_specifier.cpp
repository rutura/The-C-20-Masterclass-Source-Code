#include "noexcept_specifier.h"

namespace noexcept_specifier {
void some_function() noexcept
{
  try { throw 1; } catch (int ex) {
    fmt::println("Handling int excpetion in free function some_function()");
    // throw;
  }
}
}