#include "pointers_and_const.h"

#include <fmt/format.h>

namespace pointers_and_const {

void const_pointer_and_pointer_to_const()
{

  //A raw variable that can be modified
  /*
  fmt::println( "Raw variable that can be modified: " );

  int number {5};// Not constant, can change number any way we want
  fmt::println( "number: {}", number );
  fmt::println( "&number: {}" , fmt::ptr(&number));
  //Modify
  number = 12;
  number += 7;

  //Access - Print out
  fmt::println( "number: {}", number );
  fmt::println( "&number: {}" , fmt::ptr(&number));
  */


  // Pointer: Can modify the data and the pointer itself
  /*
  int *p_number1 {nullptr};
  int  number1{23};

  p_number1 = &number1;
  fmt::println( "Pointer and value pointed to: both modifiable." );
  fmt::println( "p_number1: {}" , fmt::ptr(p_number1)); // Address
  fmt::println( "*p_number1: {}" , *p_number1 ); // 23
  fmt::println( "number1: {}" , number1 ); // 23

  //Change the pointed to value through pointer
  fmt::println( "Modifying the value pointed to p_number1 through the pointer: " );
  *p_number1 = 432;
  fmt::println( "p_number1: {}" , fmt::ptr(p_number1));
  fmt::println( "*p_number1: {}" , *p_number1 );
  fmt::println( "number1: {}" , number1 );

  //Change the pointer itself to make it point somewhere else
  fmt::println( "Changing the pointer itself to make it point somewhere else" );
  int number2 {56};
  p_number1 = &number2;
  fmt::println( "p_number1: {}" , fmt::ptr(p_number1));
  fmt::println( "*p_number1: {}" , *p_number1 );
  fmt::println( "number1: {}" , number1 );
  fmt::println( "number2: {}" , number2 );
  */


  // Pointer to const
  /*
  // Pointer pointing to constant data : You can't modify the data through pointer
  fmt::println( "Pointer is modifiable, pointed to value is constant: " );
  int number3 {632};  // Although you can omit the const on number3 here and it is still
                      // going to compile, it is advised to be as explicit as possible in
                      // your code and put the const in front. Make your intents CLEAR.

  const int* p_number3 {&number3}; // Can't modify number3 through p_number3

  fmt::println( "p_number3: {}" , fmt::ptr(p_number3));
  fmt::println( "*p_number3: {}" , *p_number3 );

  fmt::println( "Modifying the value pointed to by p_number3 through the pointer (Compile Error): " );
  //*p_number3 = 444; // Compile error

  //Although we can't change what's pointed to by p_number3,
      //we can still change where it's pointing

  fmt::println( "Changing the address pointed to by p_number3: " );
  int number4 {872};
  p_number3 = &number4;

  fmt::println( "p_number3: {}" , fmt::ptr(p_number3));
  fmt::println( "*p_number3: {}" , *p_number3 );
  */


  // const keyword applies to the variable name.
  /*
  fmt::println( "const keyword applies to a variable name: ");

  int protected_var {10}; // Can make it const to protect it if we want.

  //p_protected_var is a pointer to const data, we can't
  //modify the data through this pointer: regardless of
  //whether the data itself is declared const or not.
  const int* p_protected_var {&protected_var};

  //*p_protected_var = 55;
  protected_var = 66;
  fmt::println( "protected_var : {}" , protected_var);
  fmt::println( "p_protected_var : {}" , fmt::ptr(p_protected_var));
  fmt::println( "*p_protected_var : {}" , *p_protected_var);

  //You can't set up a modifiable pointer to const data though,
  //You'll get a compiler error :Invalid convertion from 'const type*' to 'type*'.
  const int some_data{55};
  //int * p_some_data {&some_data}; // Compiler error.
  //*p_some_data = 66;
  */


  // Both pointer and pointed to value are constant
  /*
  const int number5 {459};
  const int* const p_number5 {&number5 };
  fmt::println( "Pointer is constant, value pointed to is constant: " );
  fmt::println( "p_number5: {}" , fmt::ptr(p_number5));
  fmt::println( "*p_number5: {}" , *p_number5);

  //Can't modify the pointed to value through the pointer
  fmt::println( "Changing value pointed to by p_number5 through the pointer (Compile Error) " );
  //*p_number5 = 222; // Error : Trying to assign to read only location

  //Can't change where the pointer is pointing to: The pointer is now itself constant
  fmt::println( "Changing the pointer p_number5 address itself (Compile Error) ");
  int number6 {333};
  //p_number5 = &number6;  // Error : Trying to assign to read only location
  */


  // Pointer is constant (can't make it point anywere else)
  // but pointed to value can change
  /*
  fmt::println("Pointer is contant, pointed to value can change : ");
  int number7{ 982 };

  int *const p_number7{ &number7 };

  fmt::println("p_number7 : {}", fmt::ptr(p_number7));
  fmt::println("*p_number7 : {}", *p_number7);
  fmt::println("Changing value pointed to through p_number7 pointer : ");

  *p_number7 = 456;
  fmt::println("The value pointed to by p_number7 now is : {}", *p_number7);

  int number8{ 2928 };
  fmt::println("Changing the address where p_number7 is pointing (Compile Error).");
  // p_number7 = &number8;
  */

}
}// namespace pointers_and_const