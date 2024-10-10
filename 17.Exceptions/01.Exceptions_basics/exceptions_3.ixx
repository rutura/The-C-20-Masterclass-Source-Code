/*
    . Exploring exceptions from different levels    
        . Function chain with no exceptions thrown
        . Function chain with exception thrown from f3() scope : Not handled anywhere
        . Function chain with exception thrown from f3() scope : Handled in f3()
        . Function chain with exception thrown from f3() scope : Handled in f2()
        . Function chain with exception thrown from f3() scope : Handled in f1()
        . Function chain with exception thrown from f3() scope : Handled the closest to main
        . The best thing to do is to handle the exception as close to the source as possible.
*/
module;

#include <fmt/format.h>

export module exceptions_3;

namespace exceptions_3{

    export void exception_thrower()
    {
        fmt::println("starting execution_thrower()");
        /*
        try {
            throw 0;// Execution will halt from here
        } catch (int ex) {
            fmt::println("Something went wrong");
        }
        */
        throw 0;
        fmt::println("ending execution_thrower()");
    }


    // No exception thrown
    namespace opt_1{
        export void f1();
        export void f2();
        export void f3();
        // Regular flow
        void f1(){
            fmt::println( "Starting f1()" );
            f2();
            fmt::println( "Ending f1()" );
        }

        void f2(){
            fmt::println( "Starting f2()" );
            f3();
            fmt::println( "Ending f2()" );
        }

        void f3(){
            fmt::println( "Starting f3()" );
            fmt::println( "Ending f3()" );
        }

    } // namespace opt_1


    //Exception thrown from f3() scope : Not handled anywhere
    namespace opt_2{
        export void f1();
        export void f2();
        export void f3();
        // Exception thrown from f3() scope : Not handled anywhere
        void f1(){
            fmt::println( "Starting f1()" );
            f2();
            fmt::println( "Ending f1()" );
        }

        void f2(){
            fmt::println( "Starting f2()" );
            f3();
            fmt::println( "Ending f2()" );
        }

        void f3(){
            fmt::println( "Starting f3()" );
            exception_thrower();
            fmt::println( "Ending f3()" );
        }
        
    } // namespace opt_2


    // Exception thrown from f3() scope : Handled in f3()
    namespace opt_3{
        export void f1();
        export void f2();
        export void f3();
        // Exception thrown from f3() scope : Handled in f3()
        void f1(){
            fmt::println( "Starting f1()" );
            f2();
            fmt::println( "Ending f1()" );
        }

        void f2(){
            fmt::println( "Starting f2()" );
            f3();
            fmt::println( "Ending f2()" );
        }

        void f3(){
            fmt::println( "Starting f3()" );
            try{
                exception_thrower();
            }catch(int ex){
                fmt::println( "Handling execution in f3()" );
            }
            fmt::println( "Ending f3()" );
        }
        
    } // namespace opt_3


    // Exception thrown from f3() scope : Handled in f2()
    namespace opt_4{

        export void f1();
        export void f2();
        export void f3();
        // Exception thrown from f3() scope : Handled in f2()
        void f1(){
            fmt::println( "Starting f1()" );
            f2();
            fmt::println( "Ending f1()" );
        }

        void f2(){
            fmt::println( "Starting f2()" );
            try{
                f3();
            }catch(int ex){
                fmt::println( "Handling execution in f2()" );
            }
            fmt::println( "Ending f2()" );
        }

        void f3(){
            fmt::println( "Starting f3()" );
            exception_thrower();
            fmt::println( "Ending f3()" );
        }
    } // namespace opt_4


    // Exception thrown from f3() scope : Handled in f1()
    namespace opt_5{
        export void f1();
        export void f2();
        export void f3();
        // Exception thrown from f3() scope : Handled in f1()
        void f1(){
            fmt::println( "Starting f1()" );
            try{
                f2();
            }catch(int ex){
                fmt::println( "Handling execution in f1()" );
            }
            fmt::println( "Ending f1()" );
        }

        void f2(){
            fmt::println( "Starting f2()" );
            f3();
            fmt::println( "Ending f2()" );
        }

        void f3(){
            fmt::println( "Starting f3()" );
            exception_thrower();
            fmt::println( "Ending f3()" );
        }
        
    } // namespace opt_5


    // Exception thrown from f3() scope : Handled the closest to main
    namespace opt_6{
        export void f1();
        export void f2();
        export void f3();
        // Exception thrown from f3() scope : Handled the closest to main
        void f1()
        {
            fmt::println("Starting f1()");
            f2(); 
            fmt::println("Ending f1()");
        }

        void f2()
        {
            fmt::println("Starting f2()");
            f3();
            fmt::println("Ending f2()");
        }

        void f3()
        {
            fmt::println("Starting f3()");
            exception_thrower();
            fmt::println("Ending f3()");
        }
        
    } // namespace opt_6
    
    
    
    


    
    
    
} // namespace exceptions_3