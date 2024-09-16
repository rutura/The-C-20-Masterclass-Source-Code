module;

#include <fmt/format.h>

export module pointer_basics;

namespace pointer_basics {


    export void tinker_with_pointers(){

        //1.Declaring and using pointers
        // Declare and initialize pointer
        /*
        int *p_number{};// Will initialize with nullptr
        double *p_fractional_number{};

        // Explicitly initialize with nullptr
        int *p_number1{ nullptr };
        int *p_fractional_number1{ nullptr };

        // Pointers to different variables are  of the same size
        fmt::println("sizeof(int): {}", sizeof(int));// 4
        fmt::println("sizeof(double): {}", sizeof(double));// 8
        fmt::println("sizeof(double*): {}", sizeof(double *));
        fmt::println("sizeof(int*): {}", sizeof(int *));
        fmt::println("sizeof(p_number1): {}", sizeof(p_number1));
        fmt::println("sizeof(p_fractional_number1): {}", sizeof(p_fractional_number1));


        // It doesn't matter if you put the * close to data type or to varible name
        int *p_number2{ nullptr };
        int *p_number3{ nullptr };
        int *p_number4{ nullptr };

        int *p_number5{}, other_int_var{};
        int *p_number6{}, other_int_var6{};// Confusing as you wonder if other_int_var6
                                            // is also a pointer to int. It is not
                                            // The structure is exactly the same for the
                                            // previous statement

        fmt::println("sizeof(p_number5): {}", sizeof(p_number5));
        fmt::println("sizeof(other_int_var): {}", sizeof(other_int_var));
        fmt::println("sizeof(p_number6): {}", sizeof(p_number6));
        fmt::println("sizeof(other_int_var6): {}", sizeof(other_int_var6));

        // It is better to separate these declarations on different lines though
        int *p_number7{};
        int other_int_var7{};// No room for confusion this time


        // Initializing pointers and assigning them data
        // We know that pointers store addresses of variables
        int int_var{ 43 };
        int *p_int{ &int_var };// The address of operator (&);

        fmt::println("Int var: {}", int_var);
        fmt::println("p_int (Address in memory): {}", fmt::ptr(p_int));

        // You can also change the address stored in a pointer any time
        int int_var1{ 65 };
        p_int = &int_var1;// Assign a different address to the pointer
        fmt::println("p_int (with different address): {}", fmt::ptr(p_int));


        // Can't cross assign between pointers of different types
        int *p_int1{ nullptr };
        double double_var{ 33 };

        // p_int = &double_var; // Compiler error

        // Dereferencing a pointer : {}
        int *p_int2{ nullptr };
        int int_data{ 56 };
        p_int2 = &int_data;

        fmt::println("value: {}", *p_int2);// Dereferencing a pointer
        */


        //2.Pointers to char
        const char *message{ "Hello World!" };
        fmt::println("message: {}", message);	//This works
        fmt::println("message: {}", *message);	//This also works

        //Can't modify a through a pointer to a string literal
        //*message = "B"; // Compiler error
        fmt::println("*message: {}", *message);

        //Printing the address of the first character
        fmt::println("message address: {}", fmt::ptr(message));

        // Allow users to modify the string
        char message1[]{ "Hello World!" };
        message1[0] = 'B';
        fmt::println("message1: {}", message1);

    }

}   // namespace pointer_basics