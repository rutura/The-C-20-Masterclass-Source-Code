module;
#include <string_view>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import templates_1;
import templates_2;
import templates_3;
import templates_4;
import templates_5;
import templates_6;

//#1: Implicit Instantiations
export void templates_1_demo(){

    using templates_1::MyClass;

    MyClass<int> my_int_instance;
    my_int_instance.safe_function();  // This works

    MyClass<double> my_double_instance;
    my_double_instance.safe_function();  // This works

    //my_int_instance.error_function(); // Notice that the code compiled, even if the call to error_function was in there.
                                        // So no checks are done before instantiating the template.
    //my_double_instance.error_function();
}

//#2: Explicit Instantiation Definition
export void templates_2_demo(){
    //All relevant parts are in the templates_2 module.
}


//#3: Explicit Instantiation Declaration and definition
// Visual C++ is having trouble resolving the add function, it can find the class though. Weird.
// Clang 18 is able to resolve both.
export void templates_3_demo(){

    using templates_3::add;
    using templates_3::Point;

    /*
    auto result1 = add(1, 2);
    Point<int> point(1, 2);
    fmt::print("Point: ({}, {})\n", point.getX(), point.getY());
    fmt::println("Result of add: {}", result1);
    */
}

//#4: Full Specialization
export void templates_4_demo(){

    using templates_4::Adder;
    using templates_4::add;

    //Class specialization
    Adder<int> adder;
    fmt::print("Sum: {}\n", adder.add(1, 2));

    Adder<const char*> adder2;
    char a[20] = "Hello"; //strcat appends to the first parameter. So, we need to have enough space. Here, 20 bytes.
    char b[] = " World";
    auto result = adder2.add(a, b);
    fmt::print("Concatenated string: {}\n", result);

    //Function specialization
    fmt::print("Sum: {}\n", add(1, 2));
    fmt::println("Concatenated string: {}", add(a, b));
}

//#5: Type Traits Example
export void templates_5_demo(){
    using templates_5::is_int;
    fmt::println("Is int: {}", is_int<int>::value);    // true
    fmt::println("Is int: {}", is_int<double>::value); // false
    fmt::println("Is int: {}", is_int<char>::value);   // false
    fmt::println("Is int: {}", is_int<std::string>::value); // false
    fmt::println("Is int: {}", is_int<long int>::value); // false
}

// #6: Partial Specialization
export void templates_6_demo(){

    using templates_6::Adder;
    using templates_6::add;

    Adder<int,double> adder;
    //adder.add(1, 2.0); // Calls the partial specialization version

    Adder<double,int> adder2;
    //adder2.add(1.0, 2); // Calls the generic version

    //add(1, 2.0); //Calls the function overload for (int, T)

    add<int,double>(1, 2.0); //Calls the generic function template

}