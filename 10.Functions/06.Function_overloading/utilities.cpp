#include "utilities.h"

#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

//Overoading with different parameters
/*int max(int a, int b)
{
  fmt::println("int overload called");
  return (a > b) ? a : b;
}

double max(double a, double b)
{
  fmt::println("double overload called");
  return (a > b) ? a : b;
}

double max(int a, double b)
{
  fmt::println("(int,double) overload called");
  return (a > b) ? a : b;
}

double max(double a, int b)
{
  fmt::println("(double,int) overload called");
  return (a > b) ? a : b;
}

double max(double a, int b, int c)
{
  fmt::println("(double,int,int) overload called");
  return a;
}

std::string_view max(std::string_view a, std::string_view b)
{
  fmt::println("(string_view,string_view) overload called");
  return (a > b) ? a : b;
}*/

//Overloading with pointer parameters
/*double max(double *numbers, size_t count)
{
  fmt::println("doubles overload called");
  double maximum{ 0 };

  for (size_t i{ 0 }; i < count; ++i) {
    if (numbers[i] > maximum) maximum = numbers[i];
  }
  return maximum;
}

int max(int *numbers, size_t count)
{
  fmt::println("ints overload called");

  int maximum{ 0 };

  for (size_t i{ 0 }; i < count; ++i) {
    if (numbers[i] > maximum) maximum = numbers[i];
  }
  return maximum;
}*/

//Overloading with references
// Ambiguous calls
/*void say_my_name(const std::string &name) { fmt::println("Your name is (ref) : {}", name); }

void say_my_name(std::string name) { fmt::println("Your name is (non ref) : {}", name); }

// Implicit conversions with references
double max(double a, double b)
{
  fmt::println("double max called");
  return (a > b) ? a : b;
}


// int& max(int& a, int& b){
const int &max(const int &a, const int &b)
{
  fmt::println("int max called");
  return (a > b) ? a : b;
}*/


//Overloading with const parameters
/*
// int max(const int a, const int b)
// {
//   fmt::println("const int max called");
//   return (a > b) ? a : b;
// }

int max(int a, int b)
{
  fmt::println("int max called");
  return (a > b) ? a : b;
}
*/


//Overloading with const pointer and pointer to const
/*
int max(int *a, int *b)
{
  fmt::println("max with int* called");
  return (*a > *b) ? *a : *b;
}

int max(const int *a, const int *b)
{
  fmt::println("max with cont int* called");
  return (*a > *b) ? *a : *b;
}

// int min(const int* a, const int* b){
//     return (*a < *b)? *a : *b;
// }


int min(const int *const a, const int *const b)
{
  fmt::println("&a : {}", fmt::ptr(&a));
  fmt::println("&b : {}", fmt::ptr(&b));
  return (*a < *b) ? *a : *b;
}
*/


//Overloading with const references
/*
int max(int &a, int &b)
{
  fmt::println("max with int& called");

  // Can change a and b through the reference
  // a = 200;// This change will be visible outside the function

  return (a > b) ? a : b;
}

int max(const int &a, const int &b)
{
  fmt::println("max with const int& called");

  // Can NOT change a and b through the reference
  // a = 200; // Will give a compiler error.
  return (a > b) ? a : b;
}
*/


//Overloading with default parameters
// Definitions
// void print_age(int age ){
//     fmt::println( "Your age is( int version)  : {}" , age );
// }

void print_age(long int age) { fmt::println("Your age is (long int version) : {}", age); }