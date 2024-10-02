/*
    . This file showcases the basics of using the spaceship operator <=> on 
        basic types like int, double, string.

    . This will lay the basics down for the next lectures where we set out
        to understand the infrastructure of the spaceship operator and how
        it simplifies logical operators like >, >=, ==, !=, <, <=.
*/
module;

#include <compare>
#include <string>
#include <fmt/format.h>

export module spaceship_ops_1;

namespace spaceship_ops_1{

    export void spaceship_op_the_basics(){

        //Regular comparison on std::string
        std::string m1{"Hello"};
        std::string m2{"World"}; // World comes after Hello in alphabetical order so it's
                                // considered to be greater.

        auto result = m1.compare(m2);
        if(result > 0){
            fmt::println( "m1 > m2" );
        }else if(result == 0){
            fmt::println( "m1 == m2" );
        }else{
            fmt::println( "m1 < m2" );
        }

        // Three way comparison operator : spaceship operator <=>
        int n1{5};
        int n2{5};
        //int n3{0};

        auto result_1 = ( n1 <=> n2);   //  The return value isn't a boolean but a three way comparison
                                        //  category type. It can be less, greater or equivalent.

        fmt::println( "n1 > n2 : {}" , ((n1 <=> n2) > 0) );
        fmt::println( "n1 >= n2 :{} ", ((n1 <=> n2) >= 0) );
        fmt::println( "n1 == n2 : {}" , ((n1 <=> n2) == 0) );
        fmt::println( "n1 < n2 : {}" , ((n1 <=> n2) < 0) );
        fmt::println( "n1 <= n2 : {}" , ((n1 <=> n2) <= 0) );


        // Strong ordering: When two types are equal, they are indistinguishable.
        int n4{5};
        int n5{5};

        fmt::println( "n4 > n5 : {}" , (n4 > n5) ); // false
        fmt::println( "n4 == n5 : {}" , (n4 == n5) ); //true :  Absolute equality
        fmt::println( "n4 < n5 : {}" , (n4 < n5) ); // false

        // Weak ordering: When two types are equivalent, they are not necessarily indistinguishable.
        // Here, the two strings contain the same message, but they are not equal.
        std::string m3{"Hello"};
        std::string m4{"HELLO"};

        fmt::println( "m3 > m4 :{} " , (m3 > m4) ); //
        fmt::println( "m3 == m4 :{} " , (m3 == m4) ); // equivalence
        fmt::println( "m3 < m4 :{} " , (m3 < m4) ); //

        // Partial ordering: Some values of the types are not comparable to others.
        double d1{ 33.9 };
        double d2{ std::numeric_limits<double>::quiet_NaN() };

        fmt::println("d1 > d2 : {}", (d1 > d2));// false
        fmt::println("d1 == d2 : {}", (d1 == d2));// false
        fmt::println("d1 < d2 : {}", (d1 < d2));// false

    }


    
} // namespace spaceship_ops_1