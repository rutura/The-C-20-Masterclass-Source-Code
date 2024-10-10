/*
    . Exploring the basics of exceptions
        . try and catch blocks
            . When we leave the try block, we can no longer manually release memory.
        . Throwing pointers
        . Potential memory leaks
        . Unhandled exceptions
        . The need for copy constructors
*/
module;

#include <fmt/format.h>
#include <memory>

export module exceptions_1;

namespace exceptions_1{

    export class Item {
    public:
        Item() { fmt::println("Item constructor called"); }
        ~Item() { fmt::println("Item destructor called"); }
    };

    export class MyException {
    public:
        MyException() = default;
        MyException(const MyException &ex) {}
    };

    //Helper methods
    export void exceptions_basics(){
        //The basics.
        // When an exception is thrown, the control immediately exits the try block and goes into the catch block.
        int a{10};
        int b{10};

        try{
            Item item; // When exception is thrown, control immediately exits the try block
                        // an automatic local variables are released
                        // But pointers may leak memory.
            if( b == 0 )
                throw 110;
            a++; // Just using a and b in here, could use them to do anything.
            b++;
            fmt::println( "Code that executes when things are fine" );
        } catch(int ex){
            fmt::println( "Something went wrong. Exception thrown : {}", ex);
        }
        fmt::println( "Done!" );

    }

    export void throwing_pointers(){
        //.Throwing a pointer : recipe for disaster
        // Throwing pointers is a recipe for disaster, as by the time
        // the catch block executes, the memory allocated and used in try
        // block is pointing to invalid data. The program may seem to work
        // sometimes but there are no guarantees you'll always get valid stuff
        // if you dereference pointers allocated in the try block.
        int c{0};
        try{
            int var{55};
            int* int_ptr = &var;
            if(c == 0)
                throw int_ptr;
            fmt::println( "Keeping doing some other things..." );
        }catch(int* ex){
            fmt::println( "Something went wrong. Exception thrown : ", *ex );
        }
        fmt::println( "END." );
    }


    export void potential_memory_leaks(){
        // Potential memory leaks
        // The destructor for Item is never called when we're thrown out of the
        // try block, and memory is leaked.
        // Using memory leaks solves the issue. Memory is released when we get out of scope.
        int d{0};
        try{
        //try_catch_blocks::Item * item_ptr = new try_catch_blocks::Item();
        std::shared_ptr<Item> item_ptr = std::make_shared<Item>();
        if(d == 0)
            throw 0;
        fmt::println( "Keeping doing some other things..." );
        }catch(int ex){
        fmt::println( "Something went wrong. Exception thrown : {}", ex );
        }
        fmt::println( "END." );
    }

    export void unhandled_exceptions(){
        // If you throw an exception and it's not handled anywhere in your code,
        // you'll get a hard crash
        throw 0;
        fmt::println( "Doing something after we throw" );

        fmt::println( "END." );
    }

    export void the_need_for_copy_constructors(){
        // If copy constructor is either deleted, protected or private, the
        // object can't be thrown as exception. You'll get a compiler error.
        try {
            MyException e;
            throw e;//

        } catch (MyException ex) {}
        fmt::println("END.");
    }
    
} // namespace exceptions_1