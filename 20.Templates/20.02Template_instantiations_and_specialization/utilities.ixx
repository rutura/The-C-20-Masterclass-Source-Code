module;
#include <string_view>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import implicit_instantiations;
import explicit_instantiation_definition;
import explicit_instantiation_declaration;
import full_specialization;
import type_trait_example;
import single_method_in_class;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void implicit_instantiations_demo(){

	// Create an instance of MyClass with int (no errors will be caused because we don't call errorFunction)
    implicit_instantiations::MyClass<int> myIntInstance;
    myIntInstance.safeFunction();  // This works

    // Create an instance of MyClass with double (again, no errors because errorFunction is not called)
    implicit_instantiations::MyClass<double> myDoubleInstance;
    myDoubleInstance.safeFunction();  // This works

    // Uncommenting the following lines will cause a compilation error because errorFunction will be instantiated
    // myIntInstance.errorFunction();
    // myDoubleInstance.errorFunction();
}

export void explicit_instantiation_definition_demo(){
	
	
}

export void explicit_instantiation_declaration_demo(){
    //auto result1 = explicit_instantiation_declaration::add(1, 2);
    //explicit_instantiation_declaration::Point<int> point(1, 2);
    //fmt::print("Point: ({}, {})\n", point.getX(), point.getY());
}

export void full_specialization_demo(){

    //Class specialization
    full_specialization::Adder<int> adder;
    fmt::print("Sum: {}\n", adder.add(1, 2));

    full_specialization::Adder<const char*> adder2;
    char a[20] = "Hello"; //strcat appends to the first parameter. So, we need to have enough space. Here, 20 bytes.
    char b[] = " World";
    auto result = adder2.add(a, b);
    fmt::print("Concatenated string: {}\n", result);

    //Function specialization
    fmt::print("Sum: {}\n", full_specialization::add(1, 2));
    fmt::println("Concatenated string: {}", full_specialization::add(a, b));
}

export void type_trait_example_demo(){
    fmt::println("Is int: {}", type_trait_example::is_int<int>::value);    // true
    fmt::println("Is int: {}", type_trait_example::is_int<double>::value); // false
    fmt::println("Is int: {}", type_trait_example::is_int<char>::value);   // false
    fmt::println("Is int: {}", type_trait_example::is_int<std::string>::value); // false
    fmt::println("Is int: {}", type_trait_example::is_int<long int>::value); // false
}

export void single_method_in_class_demo(){
    /*
    single_method_in_class::Adder<int> adder;
    fmt::print("Sum: {}\n", adder.add(1, 2));

    single_method_in_class::Adder<const char*> adder2;
    const char* a = "Hello"; //strcat appends to the first parameter. So, we need to have enough space. Here, 20 bytes.
    const char* b = " World";
    auto result = adder2.add(a, b);
    fmt::print("Concatenated string: {}\n", result);
    delete result;
    */
    single_method_in_class::BoxContainer<int> int_box;
    int_box.add(10);	
    int_box.add(11);
    int_box.add(62);
    int_box.add(330);
    int_box.add(3);
    int_box.add(7);
    int_box.add(9);
    int_box.add(8);
    std::cout << "int_box : " << int_box << std::endl;
    std::cout << "int_box.max : " << int_box.get_max() << std::endl;
    std::cout << "-------------" << std::endl;

    single_method_in_class::BoxContainer<const char*> char_ptr_box;
    char_ptr_box.add("Apple");
    char_ptr_box.add("Kiwi");
    char_ptr_box.add("Banana");
    char_ptr_box.add("Zeus");
    std::cout << "char_ptr_box : " << char_ptr_box << std::endl;
    std::cout << "char_ptr_box : " << char_ptr_box.get_max() << std::endl;
}




