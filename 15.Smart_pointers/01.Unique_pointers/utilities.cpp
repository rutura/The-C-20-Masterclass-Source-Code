#include "utilities.h"

#include <fmt/format.h>
#include "dog.h"

//Module purview
void print_msg(std::string_view msg)
{
    fmt::println("{}", msg);
}

//#2: Unique pointers as function parameters and return types
void do_something_with_dog_v1(std::unique_ptr<Dog> d) { d->print_info(); }


void do_something_with_dog_v2(const std::unique_ptr<Dog>& d)
{
    d->set_dog_name("Rior");
    d->print_info();
    // d.reset(); // Compiler error
}


std::unique_ptr<Dog> get_unique_ptr()
{
    std::unique_ptr<Dog> p_dog = std::make_unique<Dog>("Function Local");
    fmt::println("unique_ptr address(in) : {}", fmt::ptr(&p_dog));
    return p_dog; // The compiler does some optimizations and doesn't return a copy here
    // it's returning something like a reference to the local object.
    // We can prove this by looking at the address of objects in memory.
    // This is not standard behavior, some compilers may actually return
    // by value by making a copy. The compilers have some freedom to choose
    // their own way to do things.
}


void unique_pointers()
{
    // Stack variables
    /*
    {
        Dog dog1("Dog1");
        // Calling functions on stack objects
        dog1.print_info();

    }
    fmt::println( "Hitting outside scope" );
    fmt::println( "Done!" );
    */


    //----------------------------------------------------------------------------------
    // Using raw pointers : Remember to manually release memory,
    //						if you don't relase , you leak memory
    /*
        Dog* p_dog2 = new Dog("Dog2");
        int * p_int1 = new int(100);

        p_dog2->print_info();
        fmt::println( "Integer is : {}" , *p_int1 );
        fmt::println( "Integer lives at address : {}" , fmt::ptr(p_int1 ));

        //If you go out of scope withoug releasing (deleting) p_dog2 and
        // p_int1 you'll have leaked memory
        delete p_dog2; // Calls the destructor
        delete p_int1;
        */


    //----------------------------------------------------------------------------------
    // Using unique_ptr : managed memory is owned by a single pointer at any moment.
    /*
    {
        Dog * p_dog_3 = new Dog("Dog3");
        std::unique_ptr<Dog> up_dog_4{p_dog_3}; // Can also manage a previously allocated
                                                // space managed by a raw pointer. You shouldn't
                                                // try to use the raw pointer from this point on
        std::unique_ptr<Dog> up_dog_5 {new Dog("Dog5")};
        std::unique_ptr<int> up_int2{new int(200)};
        std::unique_ptr<Dog> up_dog_6{nullptr};// Can also initialize with nullptr
                        // and give it memory to manage later, we'll see how to
                        // do that with std::move later in the lecture. Just know
                        // that you can initialize a unique ptr with nullptr for now.

        //Can use unique pointer just like we use a raw pointer.
        up_dog_5->print_info(); // Calling function with -> operator
        //Assign to fundamental type
        * up_int2 = 500;
        fmt::println( "Integer is : {}" , *up_int2 ); // dereferencing
        fmt::println( "Integer lives at address : {}" , fmt::ptr(up_int2.get() ));

    }
    fmt::println( "Hitting the outside scope" );
    */


    //----------------------------------------------------------------------------------
    /*
    //using make_unique syntax. Much cleaner (C++14 )
        //Calls new internally for us, we don't have to do it ourselves
    std::unique_ptr<Dog> up_dog_7 = std::make_unique<Dog>("Dog7");
    up_dog_7->print_info();

    std::unique_ptr<int> p_int3 = std::make_unique<int>(30);
    *p_int3 =67;
    fmt::println( "Value pointed to by p_int3 is :{}"  , *p_int3 );
    fmt::println( "p_int pointing at address :{}" , fmt::ptr(p_int3.get() ));
    */

    //----------------------------------------------------------------------------------
    /*
    //Copies not allowed
    std::unique_ptr<Dog> up_dog_8 = std::make_unique<Dog>("Dog8");
    up_dog_8->print_info();
    //Can get the wrapped pointer address : useful for older raw pointer APIs
    fmt::println( "Dog8 memory address: {}" ,fmt::ptr(up_dog_8.get() ));

    // Copies and Assignments are not allowed with unique ptr
    //std::unique_ptr<Dog> up_dog_9 = up_dog_8; // Error.This also does some kind of copy
                        // More on this when we've learnt about operator overloading
    //std::unique_ptr<Dog> up_dog_10{up_dog_8}; // Error :  Copy constructor deleted
    */

    //----------------------------------------------------------------------------------

    // Can however move the pointer.
    /*
    std::unique_ptr<Dog> up_dog_11 = std::make_unique<Dog>("Dog11");
    {
        std::unique_ptr<Dog> up_dog_12 = std::move(up_dog_11); // Now up_dog_12 manages Dog11
                                                    // and up_dog_11 points to nothing(nullptr)
        up_dog_12->print_info();
        fmt::println( "Dog12 memory address : {}" , fmt::ptr(up_dog_12.get() ));

        fmt::println( "up_dog_11 is now nullptr : {}" ,fmt::ptr( up_dog_11.get() ));
        if(up_dog_11){
            fmt::println( "Pointer11 pointing to something valid" );
        }else{
            fmt::println( "Pointer11 point to nullpter" );
        }

    }
    fmt::println( "Hitting the outside scope" );
    */

    //----------------------------------------------------------------------------------
    // Can reset unique_ptr : releases memory and sets the pointer to nullptr
    // If you comment out the reset line, the destructor is called after the doing
    // something print out, if it's not commented out, we reset the pointer and the
    // destructor is called before the line : fmt::println( "Doing something" ); SHOW THIS.


    std::unique_ptr<Dog> up_dog_13 = std::make_unique<Dog>("Dog13");
    //up_dog_13.reset();// releases memory and sets pointer to nullptr

    // Can use unique pointer in if statement to see if it points somewhere valid
    if (up_dog_13)
    {
        fmt::println("up_dog_13 points somewhere valid : {}", fmt::ptr(up_dog_13.get()));
    }
    else
    {
        fmt::println("up_dog_13 points is null : {}", fmt::ptr(up_dog_13.get()));
    }
}


void unique_pointers_as_func_param_or_return_type()
{
    /*
        //Passing unique ptr to functions by value
        std::unique_ptr<Dog> p_dog_1 = std::make_unique<Dog>("Dog1");

        //Can't pass unique_ptr by value to a function : copies not allowed
    //do_something_with_dog_v1(p_dog_1);   // copy detected,


        //do_something_with_dog_v1(std::move(p_dog_1)); // Ownership will move to the body
        // of the function and memory will be
    // released when function
    returns.
    // Not what you typically want.

    fmt::println( "p_dog_1 : {}" , fmt::ptr( p_dog_1.get() ));
    fmt::println( "Hitting back the main function" );

    */

    fmt::println("------");

    /*
    std::unique_ptr<Dog> p_dog_1 = std::make_unique<Dog>("Dog1");
    Person person1("John");
    person1.adopt_dog(std::move(p_dog_1)); // The same behavior when function is part of the class
    //fmt::println( "Doing something , p_dog_1 points to :  {}" ,fmt::ptr(p_dog_1.get() ));
    */


    // An implicit move is done when object is created in place as a temporary
    // do_something_with_dog_v1(std::make_unique<Dog>("Temporary Dog"));

    //---------------------------------------------------------------------------
    /*
        //Can pass the std::unique_ptr parameter by reference.
        std::unique_ptr p_dog_2 = std::make_unique<Dog>("Dog2");
        p_dog_2->print_info();
        do_something_with_dog_v2(p_dog_2);
        fmt::println( "-----" );
        p_dog_2->print_info();
    */


    //---------------------------------------------------------------------------
    // Returning unique ptr from function by value
    /*
            std::unique_ptr<Dog> p_dog_3 = get_unique_ptr();
            fmt::println( "delimiter" );
            fmt::println( "unique_ptr address(out) : {}" ,fmt::ptr( &p_dog_3 ));

            p_dog_3->print_info();
    */

    /*
    get_unique_ptr()->print_info();

    fmt::println("function done");
    */
}


//#3: Unique pointers and arrays
void unique_pointers_and_arrays()
{
    // Array allocated on the stack
    /*
    {
        fmt::println( "Working with dog array on the stack" );
        Dog dog_array[3] {Dog("Dog1"), Dog("Dog2") , Dog("Dog3")};
        for( size_t i {0}; i < 3 ; ++i){
            dog_array[i].print_info();
        }

    }
    */

    // Array allocated on the heap
    /*
    {
        Dog * p_dog_array_raw = new Dog[3]{Dog("Dog4"), Dog("Dog5") , Dog("Dog6")};

        for( size_t i {0}; i < 3 ; ++i){
            p_dog_array_raw[i].print_info();
        }

        //If we don't delete explicitly like below. Have the line commented out, the memory
        //for the array won't be released and we won't see the destructors for Dogs 4~6 called.
        //If we delete explicitly, everything goes as expected and the destructors are called
        //when we exit this scope.

        delete[] p_dog_array_raw;
    }
    */


    // Array allocated on the heap with unique_ptr. Releases space for array automatically
    {
        // auto arr_ptr = std::unique_ptr<Dog[]> ( new Dog[3]{Dog("Dog7"), Dog("Dog8") , Dog("Dog9")});

        auto arr_ptr = std::make_unique<Dog[]>(3); // Works. Can't initialize individual elements
        // auto arr_ptr = std::make_unique<Dog[]>(3) {Dog("Dog7"), Dog("Dog8") , Dog("Dog9")};//Compiler error
        // auto arr_ptr = std::make_unique<Dog[]>{Dog("Dog7"), Dog("Dog8") , Dog("Dog9")};//Compiler error

        for (size_t i{0}; i < 3; ++i) { arr_ptr[i].print_info(); }
    }


    fmt::println("Done!");
}
