/*
    . First C++ program
    . Introduce comments
    . Introduce errors and warnings.
    . Statements and functions
    . Coding conventions. We'll go with snake case.
    . Showcase walking through the program with a debugger

*/

// One line comment

// This brings in the iostream library

/*
    This is a block comment that englobes multiple
    lines of text
*/

#include "utilities.h"

int main()
{

  // This is going to print Number1, Number2 and Number3.
  print_msg("Number1");
  print_msg("Number2");
  print_msg("Number3");
  print_number(5);


  // Compile time error- Introduce a syntax error.
  print_msg("Hello world!");

  // Run time error - dividing by zero.
  //    int value = 7/0;
  //print_number(value);

  // The program ends after the return statement.

  int num1 = 5;
  int num2 = 6;
  int result = add_numbers(num1, num2);
  print_number(result);
  return 0;
}