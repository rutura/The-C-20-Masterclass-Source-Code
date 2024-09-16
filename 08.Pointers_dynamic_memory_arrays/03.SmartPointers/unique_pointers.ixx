module;

#include <fmt/format.h>
#include <memory>

export module unique_pointers;

namespace unique_pointers{

    export void tinker_with_unique_pointers(){

        // Stack variables
        /*
        {
            int int1 = 10;
            // Calling functions on stack objects
            fmt::println("Integer is: {}", int1);

        }
        fmt::println( "Hitting outside scope" );
        fmt::println( "Done!" );
        */


        //----------------------------------------------------------------------------------
        // Using raw pointers : Remember to manually release memory,
        //						if you don't relase , you leak memory
        /*
        int* p_int2 = new int(20);
        int* p_int1 = new int(100);

        fmt::println( "Integer is: {}" , *p_int2 );
        fmt::println( "Integer lives at address: {}" , fmt::ptr(p_int2 ));

        //If you go out of scope withoug releasing (deleting) p_int2 and
        // p_int1 you'll have leaked memory
        delete p_int2; // Calls the destructor
        delete p_int1;
        */


        //----------------------------------------------------------------------------------
        // Using unique_ptr: managed memory is owned by a single pointer at any moment.
        /*
        {
            int* p_int3 = new int(30);
            std::unique_ptr<int> up_int4{p_int3}; // Can also manage a previously allocated
                                                    // space managed by a raw pointer. You shouldn't
                                                    // try to use the raw pointer from this point on
            std::unique_ptr<int> up_int5 {new int(50)};
            std::unique_ptr<int> up_int6{nullptr};// Can also initialize with nullptr
                            // and give it memory to manage later, we'll see how to
                            // do that with std::move later in the lecture. Just know
                            // that you can initialize a unique ptr with nullptr for now.

            //Can use unique pointer just like we use a raw pointer.
            fmt::println( "Integer is: {}" , *up_int5 ); // dereferencing
            fmt::println( "Integer lives at address: {}" , fmt::ptr(up_int5.get() ));

        }
        fmt::println( "Hitting the outside scope" );
        */


        //----------------------------------------------------------------------------------
        //using make_unique syntax. Much cleaner (C++14 )
        //Calls new internally for us, we don't have to do it ourselves
        /*
        std::unique_ptr<int> up_int7 = std::make_unique<int>(70);
        fmt::println( "Value pointed to by up_int7 is: {}"  , *up_int7 );
        fmt::println( "up_int7 pointing at address: {}" , fmt::ptr(up_int7.get() ));
        */

        //----------------------------------------------------------------------------------
        //Copies not allowed
        /*
        std::unique_ptr<int> up_int8 = std::make_unique<int>(80);
        fmt::println( "up_int8 pointing at address: {}" , fmt::ptr(up_int8.get() ));

        // Copies and Assignments are not allowed with unique ptr
        //std::unique_ptr<int> up_int9 = up_int8; // Error.This also does some kind of copy
                            // More on this when we've learnt about operator overloading
        //std::unique_ptr<int> up_int10{up_int8}; // Error :  Copy constructor deleted
        */

        //----------------------------------------------------------------------------------

        // Can however move the pointer.
        /*
        std::unique_ptr<int> up_int11 = std::make_unique<int>(110);
        {
            std::unique_ptr<int> up_int12 = std::move(up_int11); // Now up_int12 manages int11
                                                        // and up_int11 points to nothing(nullptr)
            fmt::println( "up_int12 pointing at address :{}" , fmt::ptr(up_int12.get() ));

            fmt::println( "up_int11 is now nullptr : {}" ,fmt::ptr( up_int11.get() ));
            if(up_int11){
                fmt::println( "Pointer11 pointing to something valid" );
            }else{
                fmt::println( "Pointer11 point to nullptr" );
            }

        }
        fmt::println( "Hitting the outside scope" );
        */

        //----------------------------------------------------------------------------------
        // Can reset unique_ptr : releases memory and sets the pointer to nullptr
        std::unique_ptr<int> up_int13 = std::make_unique<int>(130);
        up_int13.reset();// releases memory and sets pointer to nullptr

        // Can use unique pointer in if statement to see if it points somewhere valid
        if (up_int13) {
            fmt::println("up_int13 points somewhere valid : {}", fmt::ptr(up_int13.get()));
        } else {
            fmt::println("up_int13 points is null : {}", fmt::ptr(up_int13.get()));
        }

    }

}   // namespace unique_pointers