/*
    . Idea: The basics of functions and how to separate them across multiple files.
        . Will introduce some concepts about modules: 
            . Separating declarations and definitions in the same file.
            . Separating declarations and definitions across multiple files modeled as modules.
    . Function basics: 
        . First hand on functions
        . Declaration and definition
        . Multiple files
        . Declarations and definitions in the main.cpp file
            . minimum
            . maximum
            . inc_mult
        . Multiple files: 
            . declarations and definition separated in module file: math.ixx
            . Putting definitions in math_impl.cpp
            . Separating the declarations and definitions across operation and compare modules.
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
        . gcc
        . cmake
        . ninja
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

*/


//Declarations
/*
int maximum(int a, int b);  // Function declaration , prototype
                            // Signature doesn't include return type
int minimum(int a, int b);

int inc_mult(int a, int b);
*/

#include "compare.h"
#include "operations.h"
#include "utilities.h"

int main() {
    // Calling enter_bar
    /*
    enter_bar(22); // Function arguments
    enter_bar(15);

    for(size_t i{1} ; i < 20 ; ++i){
        enter_bar(i);
    }
    */

    // Calling max
    /*
    int x{22};
    int y{44};
    int result = max(100,20); // Arguments
    //Turn result into a string and print it with print_msg
    print_number(result);
    result = max(x,y);
    print_number(result);
    */


    // Calling say_hello
    /*
    say_hello();
    */

    // Calling lucy_number
    /*
    int result{};
    result = lucky_number();
    print_number(result);
    */

    //Parameters passed this way are scoped locally in the function.
    /*
    int h{ 3 };
    int i{ 4 };

    print_msg("Outside function, before increment: ");
    print_number(h);
    print_number(i);
    double incr_mult_result = increment_multiply(h, i);

    print_msg("Outside function, after increment: ");
    print_number(h);
    print_number(i);
    */

   //Declations and definitions
    int a{ 10 };
    int b{ 20 };
    int result{};
    result = maximum(a, b);
    print_number(result);

    result = minimum(a, b);
    print_number(result);

    result = inc_mult(a, b);
    print_number(result);
}


//Definitions
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