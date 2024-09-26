/*
    This file contains code that demonstrates the difference between lvalues and rvalues.
*/
module;

#include <fmt/format.h>

export module move_semantics_01;

namespace move_semantics_01{

    double add(double a, double b) { return a + b; }

    export void try_out_move_semantics(){
        int x{ 5 };// x,y and z are all lvalues, they have a memory address we
        int y{ 10 };//  can retrieve and use later on ,
        int z{ 20 };// as long as the variables are in scope.

        int *ptr = &x;

        z = (x + y);
        fmt::println("z : {}", z);
        // fmt::println( "&(x+y) : {}" , (&(x+y)) );

        fmt::println("-------");

        double result = add(10.1, 20.2);// The result of add(10.1,20.2), is stored in some memory
                                        // location for a short time, before it's assigned to result, and after it's copied
                                        // into result, the memory is reclaimed by the system.
                                        // add(10.1,20.2) is (evaluates to) an rvalue

        // fmt::println( "address of add(10.1,20.2) : {}" , &(add(10.1,20.2)) );//Error
        fmt::println("result is : {}", result);


        fmt::println("--------");

        // Grab the addresses for later use

        // int * ptr1 = &(x + y); // Compiler error. The error clearly says what's wrong here
        // int * ptr2 = &add(10.1,20.2); // Compiler error. Can only take address of an lvalue,
        //  add(10.1 , 20.2) evaluates to an rvalue.
        // int* ptr3 = &45; // Compiler error.
        int *ptr4 = &x;// OK. x is an lvalue, so we can grab its address
    }
    
}   // namespace move_semantics_01