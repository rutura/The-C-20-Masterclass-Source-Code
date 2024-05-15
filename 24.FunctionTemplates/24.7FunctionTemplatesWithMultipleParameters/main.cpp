#include <fmt/format.h>

/*
//Problematic : return depends on the order of the template arguments : BAD!
template <typename T , typename P>
P   maximum( T a, P b){
    return ((a > b) ? a : b);
}
*/

template<typename ReturnType, typename T, typename P>
// template < typename T,typename ReturnType , typename P>
// template < typename T, typename P,typename ReturnType >
ReturnType maximum(T a, P b)
{
  return ((a > b) ? a : b);
}


int main()
{

  int a{ 5 };
  double b{ 6.7 };

  auto result = maximum<int>(a, b);
  fmt::println("sizeof(result) : {}", sizeof(result));

  return 0;
}