#include <fmt/format.h>


int main()
{
  /*
  Lambda function signature :
                              [capture list] (parameters) ->return type{
                                      // Function body
                              }
  */

  // Declaring a lambda function and calling it through a name
  /*
  auto func = [](){
      fmt::println( "Hello World!" );
  };
  func();
  func();
  */


  // Declare a lambda function and call it directly
  /*
  [](){
     fmt::println( "Hello World!" );
  }();
  */


  // Lambda function that takes parameters

  /*
  [](double a, double b){
     fmt::println( "a + b : " , (a + b)  );
  }(10.0,50.0);
  */

  /*
   auto func1 = [](double a, double b){
      fmt::println( "a + b : " , (a + b)  );
   };

   func1(10,20);
   func1(5,7);
   */


  // Lambda function that returns something
  /*
  auto result = [](double a, double b){
      return a + b;
  }(10,60);

  //fmt::println( "result : " , result );
  fmt::println( "result : " , [](double a, double b){
      return a + b;
  }(10,60) );
  */


  /*
      auto func1 = [](double a, double b){
          return a + b;
      };

      auto result1 = func1(23,7);
      auto result2 = func1(9,45);

      fmt::println( "result1 : " , result1 );
      fmt::println( "result2 : " , result2 );
      fmt::println( "direct call : " , func1(5,2) );
  */

  // Explicitly specify the return type
  auto func3 = [](double a, double b) -> int { return a + b; };

  auto func4 = [](double a, double b) { return a + b; };

  double a{ 6.9 };
  double b{ 3.5 };

  auto result3 = func3(a, b);
  auto result4 = func4(a, b);

  fmt::println("result3 : {}", result3);
  fmt::println("result4 : {}", result4);
  fmt::println("sizeof(result3) : {}", sizeof(result3));// 4
  fmt::println("sizeof(result4) : {}", sizeof(result4));// 8


  fmt::println("Done!");

  return 0;
}