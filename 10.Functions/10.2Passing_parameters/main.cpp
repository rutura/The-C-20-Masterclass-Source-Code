/*
    . Passing parameters to functions: 
        . By value: 
            . The function receives a copy of the value passed to it. 
            . The original value is not modified.

        . By reference:
            . The function receives a reference to the value passed to it. 
            . The original value is modified.

        . By Pointer:
            . The function receives a pointer to the value passed to it. 
            . The original value is modified.
        
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

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.
        . In this case, the price to adhere to our philosophy is too high compared to the value 
            we get. So we'll just include the fmt library in the main module.

*/

// One line comment
#include <fmt/format.h>

import utilities;

//Pass by avalue
/*
void say_age(int age)
{
    // Parameter
    ++age;
    fmt::println("Hello, you are {} years old! &age: {}", age, fmt::ptr(&age));
}
*/

//Pass by const value
//Can't have this const age function together with the one on top because they achieve the same thing in the eyes of the compiler.
//The warning or error you get may be different.
/*
void say_age(const int age)
{
  //++age;  //Can't assign to a variable that is const
  fmt::println("Hello, you are {} years old! &age: ", age, fmt::ptr(&age));
}
*/

//Pass by pointer
/*
void say_age(int *age)
{// Parameter
  ++(*age);
  fmt::println("Hello ,you are {} years old! &age: {}", *age, fmt::ptr(&age));// 24
}
*/

//Pass by pointer to const
/*
int dog_count{ 10 };// Global
void say_age(const int *age)    //The value pointed to is constant 
{
    //++(*age); //One way to do this

    //Another way to do this
    // int value = *age;
    // ++value;
    // *age = value;
    fmt::println("Hello , you are {}  years old! &age :{} ", *age, fmt::ptr(&age));// 24

    //But we can make the pointer point somewhere else
    age = &dog_count; //This compiles
}
*/

//Pass by const pointer to const

int dog_count{ 10 };// Global
void say_age(const int *const age)
{
    //++(*age); // The value pointed to is const.
    fmt::println("Hello , you are {} years old! &age : {}", *age, fmt::ptr(&age));// 24
    //age = & dog_count; // The pointer itself is const, you can't make it point somewhere else.
}

int main() {

    //Pass by value
    /*
    int age{ 23 };// Local
    fmt::println("age (before call): {} &age: {}", age, fmt::ptr(&age));
    say_age(age);// Argument
    fmt::println("age (after call): {} &age: {}", age, fmt::ptr(&age));
    */

    //Pass by const value
    /*
    int age{ 23 };// Local
    fmt::println("age (before call): {} &age: {}", age, fmt::ptr(&age));
    say_age(age);// Argument
    fmt::println("age (after call): {} &age: ", age, fmt::ptr(&age));
    */

    //Pass by pointer
    /*
    int age{ 23 };// Local
    fmt::println("age (before call), {} &age: {} ", age, fmt::ptr(&age));// 23
    say_age(&age);// Argument
    fmt::println("age (after call), {} &age: {}", age, fmt::ptr(&age));// 24
    */


    //Pass by pointer to const
    /*
    int age{ 23 };// Local
    fmt::println("age (before call): {} &age: {}", age, fmt::ptr(&age));// 23
    say_age(&age);// Argument
    fmt::println("age (after call): {} &age: {}", age, fmt::ptr(&age));// 24
    */


    //Pass by const pointer to const
    /*
    int age{ 23 };// Local
    fmt::println("age (before call): {} &age: {}", age, fmt::ptr(&age));
    say_age(&age);// Argument
    fmt::println("age (after call): {} &age: {}", age, fmt::ptr(&age));
    */
}