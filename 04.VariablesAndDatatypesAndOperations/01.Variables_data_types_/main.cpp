/*
    . Exploring variables and data types
    . Topics: 
        . Data representation in memory
            . Integers
        . Number systems for integers
            . Decimal, octal, hexadecimal, and binary.
        . Data representation in memory
            . Floating point types
        . Type ranges for ints and floats
            
    . Build instructions: 
        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code): 
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from the start.

        . Can also use presets on the command line.
    . Dependencies: 
        . gcc 14 or up (can be official container)
        . cmake 3.29 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version
*/

// One line comment
//#include <fmt/format.h>

#include "utilities.h"

int main() {
      // Integers and number systems
      /*
      int number1 = 15;// Decimal
      int number2 = 017;// Octal
      int number3 = 0x0F;// Hexadecimal
      int number4 = 0b00001111;// Binary

      fmt::println("number1 : {}", number1);
      fmt::println("number2 : {}", number2);
      fmt::println("number3 : {}", number3);
      fmt::println("number4 : {}", number4);
      */

     //Number systems exported into a module
     //number_systems();

     // Floating point types
     // floats offer 7 digits of precision while double offers 15 digits of precision.
     // The range of float is 1.17549e-38 to 3.40282e+38 
     //The range of double is 2.22507e-308 to 1.79769e+308
     //The range of long double is 3.3621e-4932 to 1.18973e+4932
     // Using https://ciechanow.ski/exposing-floating-point/ as a reference

     float num1 = -343.53125f;
     double num2 = -343.53125;
     long double num3 = -343.53125l;

     
     represent_float(num1);

     //Type ranges for ints and floats
     //print_type_ranges();


}