#include "utilities.h"


void print_msg(std::string_view msg) { fmt::println("{}", msg); }

// Function that takes a single parameter, and doesn't
// give back the result explicitly
void enter_bar(size_t age)
{
  // Functions parameters
  if (age > 18) { fmt::println("You're {} years old. Please proceed.", age); } else {
    fmt::println("Sorry, you're too young for this. No offense! ");
  }
  return;
}

// Function that doesnt' take parameters and returns nothing
void say_hello()
{
  fmt::println("Hello there");
  return;// You could omit this return statement for functions returning void
}

// Parameters passed this way are scoped localy in the function.
// Changes to them are not visible outside the function. What we
// have inside the function are actually COPIES of the arguments
// passed to the function.
double increment_multiply(double a, double b)
{

  fmt::println("Inside function , before increment : ");
  fmt::println("a: {}", a);
  fmt::println("b: {}", b);

  int result = ((++a) * (++b));

  fmt::println("Inside function , after increment : ");
  fmt::println("a: {}", a);
  fmt::println("b: {}", b);

  // Returning the result
  return result;
}


//Declarations in an block
/*
{
    int maximum(int a, int b);  // Function declaration , prototype
                            // Signature doesn't include return type
    int minimum(int a, int b);

    int inc_mult(int a, int b);
}
*/


//Implementations
/*int maximum(int a, int b)
{
  if (a > b) return a;
  else return b;
}

int minimum(int a, int b)
{
  if (a < b) return a;
  else return b;
}

int inc_mult(int a, int b)
{
  int result = ((++a) * (++b));
  return result;
}*/