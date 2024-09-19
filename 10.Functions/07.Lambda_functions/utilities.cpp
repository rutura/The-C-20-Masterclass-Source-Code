#include "utilities.h"

#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

//Declaring and using lambdas
void declare_and_use_lambda_func()
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

}

void capture_lists()
{

  // Capture lists
  /*
  double a{10};
  double b{20};

  auto func = [a,b](){
          fmt::println( "a + b : " , a + b );
  };
  func();

  //Capturing by value
  int c{42};

  auto func = [c](){
          fmt::println( "Inner value : {}{}{}" , c , " &inner : " ,fmt::ptr(&c ));
  };

  for(size_t i{} ; i < 5 ;++i){
          fmt::println( "Outer value : {}{}{}" , c , " &outer : " , fmt::ptr(&c ));
          func();
          ++c;
  };
  */

  // Capture by reference
  int c{ 42 };

  auto func = [&c]() { fmt::println("Inner value : {} {}{}", c, " &inner : ", fmt::ptr(&c)); };

  for (size_t i{}; i < 5; ++i) {
    fmt::println("Outer value : {} {}{}", c, " &outer : ", fmt::ptr(&c));
    func();
    ++c;
  }

}

void capture_all_lists()
{

  // Capture everything by value
  /*
  int c{42};

  auto func = [=](){
          fmt::println("Inner value : {}" , c );
  };

  for(size_t i{} ; i < 5 ;++i){
          fmt::println("Outer value : {}" , c );
          func();
          ++c;
  }
  */


  // Capturing all reference
  int c{ 42 };
  int d{ 5 };

  auto func = [&]() {
    fmt::println("Inner value : {}", c);
    fmt::println("Inner value(d) : {}", d);
  };

  for (size_t i{}; i < 5; ++i) {
    fmt::println("Outer value : {}", c);
    func();
    ++c;
  }
}