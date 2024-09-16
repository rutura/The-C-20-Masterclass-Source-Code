module;

#include <fmt/format.h>
#include <memory>

export module shared_pointers;

namespace shared_pointers{

    export void tinker_with_shared_pointers(){

        // shared pointers to fundamental types
        /*
        {

            std::shared_ptr<int> int_ptr_1 {new int{20}};

            fmt::println( "The pointed to value is: {}" , *int_ptr_1 );
            *int_ptr_1 = 40; // Use the pointer to assign
            fmt::println( "The pointed to value is: {}" , *int_ptr_1 );
            fmt::println( "Use count: {}" , int_ptr_1.use_count() ); //1
            fmt::println( "----" );

            //Copying

            std::shared_ptr<int> int_ptr_2 = int_ptr_1; // Use count : 2

            fmt::println( "The pointed to value is (through int_ptr2): {}" , *int_ptr_2 );
            *int_ptr_2 = 70;
            fmt::println( "The pointed to value is (through int_ptr2): {}" , *int_ptr_2 );
            fmt::println( "Use count for int_ptr_1: {}" , int_ptr_1.use_count() );
            fmt::println( "Use count for int_ptr_2: {}" , int_ptr_2.use_count() );


            //Other ways to initialize shared pointers
            fmt::println( "-----" );
            std::shared_ptr<int> int_ptr_3; // nullptr
            int_ptr_3 = int_ptr_1; // Use count : 3

            std::shared_ptr<int> int_ptr_4{nullptr};
            int_ptr_4 = int_ptr_1; // Use count : 4

            std::shared_ptr<int> int_ptr_5{int_ptr_1}; // Use count : 5

            fmt::println( "The pointed to value is (through int_ptr5): {}" , *int_ptr_5 );
            *int_ptr_5 = 100;
            fmt::println( "The pointed to value is (through int_ptr5): {}" , *int_ptr_5 );

            fmt::println( "Use count for int_ptr_1: {}" , int_ptr_1.use_count() );
            fmt::println( "Use count for int_ptr_2: {}" , int_ptr_2.use_count() );
            fmt::println( "Use count for int_ptr_3: {}" , int_ptr_3.use_count() );
            fmt::println( "Use count for int_ptr_4: {}" , int_ptr_4.use_count() );
            fmt::println( "Use count for int_ptr_5: {}" , int_ptr_5.use_count() );


            //Use a shared pointer to manage an already existing piece of memory
            fmt::println( "-----" );
            fmt::println( "Use a shared pointer to manage an already existing piece of memory:" );
            int * int_ptr_raw = new int(33);

            std::shared_ptr<int> int_ptr_6 {int_ptr_raw};
            int_ptr_raw = nullptr;
            fmt::println( "The value pointed to by int_ptr_raw is (through int_ptr_6): {}" , *int_ptr_6 );
            fmt::println( "Use count for int_ptr_6 is: {}" , int_ptr_6.use_count() );
            fmt::println( "raw pointer: {}" , fmt::ptr(int_ptr_raw ));
            fmt::println( "int_ptr_6.get(): {}" ,fmt::ptr( int_ptr_6.get() ));


            //Reset : decrements the use count and sets the pointer to nullptr
            fmt::println( "Reset..." );
            int_ptr_5.reset(); // decrements reference count and sets int_ptr5 to nullptr
                            // after this if you show use count, for int_ptr5,you'll get 0
            fmt::println( "Use count for int_ptr_1: {}" , int_ptr_1.use_count() );
            fmt::println( "Use count for int_ptr_2: {}" , int_ptr_2.use_count() );
            fmt::println( "Use count for int_ptr_3: {}" , int_ptr_3.use_count() );
            fmt::println( "Use count for int_ptr_4: {}" , int_ptr_4.use_count() );
            fmt::println( "Use count for int_ptr_5: {}" , int_ptr_5.use_count() );
            fmt::println( "int_ptr_5.get(): {}" , fmt::ptr(int_ptr_5.get() ));


            //Can get the raw pointer address and use the ptr in if statements (castable to bool)
            fmt::println( "int_ptr_4: {}" , fmt::ptr(int_ptr_4.get()));

            if(int_ptr_4){
                fmt::println( "int_ptr_4 pointing to something valid" );
            }else{
                fmt::println( "int_ptr_4 pointing to nullptr" );
            }


            fmt::println( "Resetting the pointers... " );
            int_ptr_4.reset();
            int_ptr_3.reset();
            int_ptr_2.reset();
            int_ptr_1.reset();
            fmt::println( "Use count for int_ptr_1: {}" , int_ptr_1.use_count() );
            fmt::println( "Use count for int_ptr_2: {}" , int_ptr_2.use_count() );
            fmt::println( "Use count for int_ptr_3: {}" , int_ptr_3.use_count() );
            fmt::println( "Use count for int_ptr_4: {}" , int_ptr_4.use_count() );
            fmt::println( "Use count for int_ptr_5: {}" , int_ptr_5.use_count() );

        }
        */

        // make_shared
        {
            std::shared_ptr<int> int_ptr_6 = std::make_shared<int>(55);
            fmt::println("The value pointed to by int_ptr_6 is: {}", *int_ptr_6);


            fmt::println("int_ptr_6 use count: {}", int_ptr_6.use_count());// 1


            // Share the object(data) with other shared_ptr's
            fmt::println("Share the object(data) with other shared_ptr's");
            std::shared_ptr<int> int_ptr_7{ nullptr };
            int_ptr_7 = int_ptr_6;

            fmt::println("int_ptr6 use count : {}", int_ptr_6.use_count());

            fmt::println("Reset ptr6's");
            int_ptr_6.reset();// decrement reference count, and set int_ptr6 to nullptr
                            // if reference count is zero, release the managed memory
            fmt::println("int_ptr_6 use count : {}", int_ptr_6.use_count());
            fmt::println("int_ptr_7 use count : {}", int_ptr_7.use_count());
        }	
    }

}   // namespace shared_pointers