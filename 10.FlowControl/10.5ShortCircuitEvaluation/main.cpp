#include <fmt/format.h>

bool car()
{
  fmt::println("car function running");
  return false;
}

bool house()
{
  fmt::println("house function running");
  return true;
}
bool job()
{
  fmt::println("job function running");
  return false;
}
bool spouse()
{
  fmt::println("spouse function running");
  return false;
}


int main()
{

  /*
      bool a{ true };
      bool b{ true };
      bool c{ true };
      bool d{ false };

      bool p{ false };
      bool q{ false };
      bool r{ false };
      bool m{ true };


      //AND : If one of the operands is 0, the result is 0
      fmt::println( "AND short circuit" );
      bool result = a && b && c && d;
      fmt::println( "result : {}", result );

      //OR : If one of the operands is 1, the result is 1.
      fmt::println( "OR short circuit" );
      result = p || q || r || m;
      fmt::println( "result : {}",  result );
  */


  /*
   if (car() && house() && job() && spouse()) {
       fmt::println( "I am happy" );
   }
   else {
       fmt::println( "I am sad" );
   }
   */

  if (car() || house() || job() || spouse()) {
    fmt::println("I am happy");
  } else {
    fmt::println("I am sad");
  }

  return 0;
}