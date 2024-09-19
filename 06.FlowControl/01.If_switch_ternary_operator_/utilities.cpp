#include "utilities.h"

#include <iostream>
#include <utility>
//#include <fmt/format.h>

/*https://en.cppreference.com/w/cpp/utility/unreachable*/
[[noreturn]] inline void unreachable()
{
  // Uses compiler specific extensions if possible.
  // Even if no extension is used, undefined behavior is still raised by
  // an empty function body and the noreturn attribute.
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
  __assume(false);
#else // GCC, Clang
  __builtin_unreachable();
#endif
}

void print_msg(std::string_view msg)
{
  //fmt::println("{}",msg);
}

bool car()
{
  //fmt::println("car function running");
  return false;
}

bool house()
{
  //fmt::println("house function running");
  return true;
}

bool job()
{
  //fmt::println("job function running");
  return false;
}

bool spouse()
{
  //fmt::println("spouse function running");
  return false;
}

//std::unreachable: C++ 23
void handleColor(int color)
{
  switch (color) {
  case Red:
    //fmt::println("Handling Red");
    std::cout << "Handling Red" << std::endl;
    break;
  case Green:
    //fmt::println("Handling Green");
    std::cout << "Handling Green" << std::endl;
    break;
  case Blue:
    //fmt::println("Handling Blue");
    std::cout << "Handling Blue" << std::endl;
    break;
  default:
    // We expect that all cases are covered, so reaching here should never happen.
    unreachable();
  }
}

void do_work()
{

  //1. If and else statements
  /*
  int number1{ 75 };
    int number2{ 60 };
    bool result = (number1 < number2);// Expression yielding the condition


//Free standing if statement
fmt::println( "free standing if statement" );
    //if(result){
        if(result == true){
        fmt::println("{} is less than {}" , number1, number2 );
    }

    //if(!result){
        if(!(result == true)){
        fmt::println( " {}is NOT less than{} " , number1,number2 );
    }
  */


  // Using else
  /*
fmt::println( "using the else clause : " );
if(result == true){
        fmt::println(" {} is less than {}" , number1, number2 );
    }else{
        fmt::println( "{} is NOT less than {}" , number1, number2 );
    }
  */


  // Use expression as condition directly
  /*
fmt::println( "Using expression as condition : " );
if(number1 < number2){
        fmt::println("{} is less than {}" ,number1, number2 );
    }else{
        fmt::println("{} is NOT less than {}" ,number1, number2 );
    }
  */


  // Nesting if statements
  /*
    fmt::println("Nesting if statements");

    bool red = false;
    bool green{ true };
    bool yellow{ false };
    bool police_stop{ true };

     //   If green : go
     //   If red, yellow : stop
     //   If green and police_stop : stop

    if(red){
        fmt::println( "Stop" );
    }
    if(yellow){
        fmt::println( "Slow down" );
    }
if(green){
  fmt::println( "Go" );
}

fmt::println( "Police officer stops(verbose)" );
if(green){
      if(police_stop){
          fmt::println( "Stop" );
      }else{
             fmt::println( "Go" );
         }
     }

    fmt::println("Police officer stops(less verbose)");
    if (green && !police_stop) {
      fmt::println("Go");
    } else {
      fmt::println("Stop");
    }
  */

  //If with initializer
  /*
    bool go{ true };
    if (int speed{ 10 }; go) {
      fmt::println("speed : {}", speed);

      if (speed > 5) {
        fmt::println("Slow down!");
      } else {
        fmt::println("All good!");
      }
    } else {
      fmt::println("speed : {}", speed);
      fmt::println("Stop");
    }
  */

  //2.else if
  /*
  int tool{ Eraser };

    if (tool == Pen) {
      fmt::println("Active tool is pen");
      // Do the actual painting
    } else if (tool == Marker) {
      fmt::println("Active tool is Marker");
    } else if (tool == Eraser) {
      fmt::println("Active tool is Eraser");
    } else if (tool == Rectangle) {
      fmt::println("Active tool is Rectangle");
    } else if (tool == Circle) {
      fmt::println("Active tool is Circle");
    } else if (tool == Ellipse) {
      fmt::println("Active tool is Ellipse");
    }
  */


  //3. Switch statement
  /*
  int tool{ Eraser };

  switch (tool) {
          case Pen: {
                  fmt::println("Active tool is Pen");
          } break;

          case Marker: {
                  fmt::println("Active tool is Marker");
          } break;

          case Eraser:
          case Rectangle:
          case Circle: {
                  fmt::println("Drawing Shapes");
          } break;

          case Ellipse: {
                  fmt::println("Active tool is Ellipse");
          } break;

          default: {
                  fmt::println("No match found");
          } break;
  }
  */

  //Switch with initializer
  /*
  int tool{ Eraser };

  switch (double strength{ 3.56 }; tool) {
          case Pen: {
                  fmt::println("Active tool is Pen. strength : {}", strength);
          } break;

          case Marker: {
                  fmt::println("Active tool is Marker. strength : {}", strength);
          } break;


          case Eraser:
          case Rectangle:
          case Circle: {
                  fmt::println("Drawing Shapes. strength : {}", strength);
          } break;

          case Ellipse: {
                  fmt::println("Active tool is Ellipse. strength : {}", strength);
          } break;

          default: {
                  fmt::println("No match found. strength : {}", strength);
          } break;
  }
  */

  //4. Short circuit evaluations
  /*
bool a{ true };
bool b{ true };
bool c{ true };
bool d{ false };

bool p{ false };
bool q{ false };
bool r{ false };
bool m{ true };


//AND : If one of the operands is false, the result is false.
fmt::println( "AND short circuit" );
bool result = a && b && c && d;
fmt::println( "AND - result : {}", result );

//OR : If one of the operands is true, the result is true.
fmt::println( "OR short circuit" );
result = p || q || r || m;
  fmt::println( "OR - result : {}", result );
  */

  /*
  if (car() && house() && job() && spouse()) {
      fmt::println( "AND - I am happy" );
  }
  else {
      fmt::println( "AND - I am sad" );
  }

 if (car() || house() || job() || spouse()) {
   fmt::println("OR - I am happy");
 } else {
   fmt::println("OR - I am sad");
 }
 */


  //5. Ternary operator
  /*
  int max{};

int a{ 35 };
int b{ 200 };

//  if(a >  b){
//     max = a;
//  }else{
//       max = b;
//  }

max = (a > b) ? a : b;// Ternary operator

fmt::println("max :{} ", max);
  */

  //6. std::unreachable: C++ 23
  handleColor(Red);
  handleColor(Green);
  handleColor(Blue);
}