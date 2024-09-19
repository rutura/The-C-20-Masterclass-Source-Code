#include "exceptions_diff_levels.h"

#include <fmt/format.h>

namespace exceptions_diff_levels {
void exception_thrower()
{
  fmt::println("starting execution_thrower()");
  try {
    throw 0;// Execution will halt from here
  } catch (int ex) { fmt::println("Something went wrong"); }
  fmt::println("ending execution_thrower()");
}

// Definitions
// Regular flow
/*
void f1(){
    fmt::println( "Starting f1()" );
    f2();
    fmt::println( "Ending f1()" );
}

void f2(){
    fmt::println( "Starting f2()" );
    f3();
    fmt::println( "Ending f2()" );
}

void f3(){
    fmt::println( "Starting f3()" );
    fmt::println( "Ending f3()" );
}
*/

//*******************************************************************************
// Exception thrown from f3() scope : Not handled anywhere
/*
void f1(){
    fmt::println( "Starting f1()" );
    f2();
    fmt::println( "Ending f1()" );
}

void f2(){
    fmt::println( "Starting f2()" );
    f3();
    fmt::println( "Ending f2()" );
}

void f3(){
    fmt::println( "Starting f3()" );
    exception_thrower();
    fmt::println( "Ending f3()" );
}

*/

//*******************************************************************************
// Exception thrown from f3() scope : Handled in f3()
/*
void f1(){
    fmt::println( "Starting f1()" );
    f2();
    fmt::println( "Ending f1()" );
}

void f2(){
    fmt::println( "Starting f2()" );
    f3();
    fmt::println( "Ending f2()" );
}

void f3(){
    fmt::println( "Starting f3()" );
    try{
        exception_thrower();
    }catch(int ex){
        fmt::println( "Handling execution in f3()" );
    }
    fmt::println( "Ending f3()" );
}
*/

//*******************************************************************************
// Exception thrown from f3() scope : Handled in f2()
/*
void f1(){
    fmt::println( "Starting f1()" );
    f2();
    fmt::println( "Ending f1()" );
}

void f2(){
    fmt::println( "Starting f2()" );
    try{
        f3();
    }catch(int ex){
        fmt::println( "Handling execution in f2()" );
    }
    fmt::println( "Ending f2()" );
}

void f3(){
    fmt::println( "Starting f3()" );
    exception_thrower();
    fmt::println( "Ending f3()" );
}
*/
//*******************************************************************************
// Exception thrown from f3() scope : Handled in f1()
/*
void f1(){
    fmt::println( "Starting f1()" );
    try{
        f2();
    }catch(int ex){
        fmt::println( "Handling execution in f1()" );
    }
    fmt::println( "Ending f1()" );
}

void f2(){
    fmt::println( "Starting f2()" );
    f3();
    fmt::println( "Ending f2()" );
}

void f3(){
    fmt::println( "Starting f3()" );
    exception_thrower();
    fmt::println( "Ending f3()" );
}
*/

//*******************************************************************************

// Exception thrown from f3() scope : Handled the closest to main
void f1()
{
  fmt::println("Starting f1()");
  f2();
  fmt::println("Ending f1()");
}

void f2()
{
  fmt::println("Starting f2()");
  f3();
  fmt::println("Ending f2()");
}

void f3()
{
  fmt::println("Starting f3()");
  exception_thrower();
  fmt::println("Ending f3()");
}

}