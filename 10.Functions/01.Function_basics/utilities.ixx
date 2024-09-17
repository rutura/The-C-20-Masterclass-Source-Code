module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 


export void print_number(auto number) {
	fmt::println("{}",number);
}

// Function that takes a single parameter, and doesn't
// give back the result explicitly
export void enter_bar(size_t age)
{// Functions parameters
  if (age > 18) {
    fmt::println("You're {} years old. Please proceed.", age);
  } else {
    fmt::println("Sorry, you're too young for this. No offense! ");
  }
  return;
}


// Function that takes multiple parameters and returns the result of the computation
export int max(int a, int b)
{
  if (a > b)
    return a;
  else
    return b;
}

// Function that doesnt' take parameters and returns nothing
export void say_hello()
{
  fmt::println("Hello there");
  return;// You could omit this return statement for functions returning void
}


// Function that takes no parameters and return something
export int lucky_number() { return 99; }


// Parameters passed this way are scoped localy in the function.
// Changes to them are not visible outside the function. What we
// have inside the function are actually COPIES of the arguments
// passed to the function.
export double increment_multiply(double a, double b)
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

//Declarations in an export block
/*
export {
	int maximum(int a, int b);  // Function declaration , prototype
                            // Signature doesn't include return type
	int minimum(int a, int b);

	int inc_mult(int a, int b);
}
*/


//Implementations
/*
int maximum(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int minimum(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}

int inc_mult(int a, int b) {
    int result = ((++a) * (++b));
    return result;
}
*/