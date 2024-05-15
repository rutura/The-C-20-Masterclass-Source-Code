#include <fmt/format.h>


int main()
{

  auto func = []<typename T, typename P>(T a, P b) { return a + b; };

  char a{ 'c' };
  int b{ 63 };

  auto result = func(a, b);
  fmt::println("result : {}", result);
  fmt::println("sizeof(result) : {}", sizeof(result));


  return 0;
}