#include "exceptions.h"
#include <fmt/format.h>


void do_something(size_t i)
{
  if (i == 2) { throw CriticalError("i is 2"); }

  if (i == 3) { throw SmallError("i is 3"); }

  if (i == 4) { throw Warning("i is 4"); }
  fmt::println("Doing something at iteration : {}", i);
}


int main()
{
  for (size_t i{ 0 }; i < 5; ++i) {
    try {
      try {
        do_something(i);
      } catch (SomethingIsWrong &ex_inner) {
        if (typeid(ex_inner) == typeid(Warning)) {
          fmt::println(" {}-Inner catch block ,Exception cought : {}", typeid(ex_inner).name(), ex_inner.what());
        } else {
          throw;//
          // throw ex_inner;//This will do a copy, and there will be slicing.Beware.
        }
      }
    } catch (SomethingIsWrong &ex_outer) {
      fmt::println(" {}-Outer catch block, Exception cought : {}", typeid(ex_outer).name(), ex_outer.what());
    }
  }// End of for loop


  return 0;
}
