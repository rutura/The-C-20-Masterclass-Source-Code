#include <fmt/format.h>


int main()
{

  int max{};

  int a{ 35 };
  int b{ 200 };

  fmt::println("using regular if ");

  /*
  if(a >  b){
      max = a;
  }else{
      max = b;
  }
  */

  max = (a > b) ? a : b;// Ternary operator

  fmt::println("max :{} ", max);


  return 0;
}