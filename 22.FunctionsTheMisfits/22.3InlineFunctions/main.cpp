#include <fmt/format.h>

inline int max(int a, int b)
{
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int main()
{

  int a{ 15 };
  int b{ 8 };

  //    fmt::println("max : {}" , max(a,b) );

  // What the compiler might do to inline your function call
  fmt::print("max : ");
  if (a > b) {
    fmt::println("{}", a);
  } else {
    fmt::println("{}", b);
  }


  return 0;
}