#include "exceptions.h"
#include <fmt/format.h>

void some_function(size_t i)
{
  if (i == 0) throw 1;
  if (i == 2) throw "const char*-Hello there";
  if (i == 3) throw CriticalError("Something is wrong");
  if (i == 4) throw std::string("std::string-Hello there");
}


int main()
{

  try {
    for (size_t i{}; i < 5; ++i) {
      try {
        some_function(i);
      } catch (int ex) {
        fmt::println("int handler- Cought an integer");
      } catch (...) {
        fmt::println("Inner... handler , Cought some exception");
        throw;
      }
    }
  } catch (const std::string &ex) {
    fmt::println("Cought some string exception");
  } catch (...) {
    fmt::println("Outer ...handler cought some other exception");
  }


  return 0;
}