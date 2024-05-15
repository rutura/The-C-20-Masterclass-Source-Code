#include <fmt/format.h>

/*
template <typename T, typename P>
decltype(auto) func_add( T a, P b){
    return a + b;
}
*/


auto func_add(auto a, auto b) { return a + b; }


int main()
{

  int a{ 7 };
  double b{ 78.2 };

  auto result = func_add(a, b);
  fmt::println("result : {}", result);
  fmt::println("sizeof(result) : {}", sizeof(result));

  return 0;
}