/*
    This file contains code that demonstrates rvalue references.
    . The purpose of an rvalue reference is to make it possible for a particular function
            overload to be chosen when an rvalue is involved.
*/
module;

#include <fmt/format.h>

export module move_semantics_02;

namespace move_semantics_02{

    struct Position{
        unsigned int x;
        unsigned int y;
    };

    //Two functions, one takes an lvalue reference, the other takes an rvalue reference
    /*
    void print_position(Position &pos){
        fmt::print("Position(lvalue ref): x = {}, y = {}\n", pos.x, pos.y);
    }
    */

   void normalize_position(Position&& pos){
        fmt::print("Position(rvalue ref): x = {}, y = {}\n", pos.x, pos.y);
    }

    void print_position(Position &&pos){
        fmt::print("Position(rvalue ref): x = {}, y = {}\n", pos.x, pos.y);
        //normalize_position(pos); //pos is named here, so it's an lvalue, we need to cast it to an rvalue reference
        //normalize_position(std::move(pos)); //pos is now an rvalue reference
    }

    double add(double a, double b) { return a + b; }

    export void try_out_move_semantics(){

        /*
        int x{ 5 };
        int y{ 10 };

        int &&result = x + y;   // If a temporary is referenced by an rvalue reference,
                                // it's lifetime is extended to the lifetime of the reference.

        double &&outcome = add(10.1, 20.2);

        fmt::println("result : {}", result);
        fmt::println("outcome : {}", outcome);
        */

        //print_position(Position{ 10, 20 }); // The rvalue reference overload is called here

        Position pos{ 30, 40 };
        //print_position(pos); // The lvalue reference overload is called here

        //If the lvalue reference overload is commented out, the rvalue reference overload is called, 
        //when we cast pos to an rvalue reference with std::move
        //The only thing std::move() does is cast an lvalue to an rvalue reference; that is, it does not do any actual
        // moving. However, by returning an rvalue reference, it allows the compiler to find an overload of
        // print_position() accepting an rvalue reference, which can then perform the moving.
        //print_position is not doing any moving here. We'll explore move semantics proper shortly.
        print_position(std::move(pos)); // The rvalue reference overload is called here

    }
    
}   // namespace move_semantics_02