module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import recursion;
import variadic_function_templates;
import variadic_class_templates;
import fold_expressions;

import templates_1;
import templates_2;
import templates_3;

//#1: Template recursion
export void templates_1_demo(){
	fmt::println("Factorial of 5 using bare recursion: {}", templates_1::factorial_bare(5));
	fmt::println("Factorial of 5 using template recursion: {}", templates_1::Factorial<5>::value);
	fmt::println("Factorial of 5 using constexpr function: {}", templates_1::factorial(5));
}


//#2: Variadic function templates
export void templates_2_demo(){
	//Do the sums from 1 element up to 5 elements
	//auto value = variadic_function_templates::add(1);	//This will not compile,we need at least two parameters.
	fmt::println("Sum of 2 elements: {}", templates_2::impl_1::add(1, 2));
	fmt::println("Sum of 3 elements: {}", templates_2::impl_1::add(1, 2, 3));
	fmt::println("Sum of 4 elements: {}", templates_2::impl_1::add(1, 2, 3, 4));
	fmt::println("Sum of 5 elements: {}", templates_2::impl_1::add(1, 2, 3, 4, 5));
	fmt::println("Sum of 5 elements using add2: {}", templates_2::impl_2::add2(1, 2, 3, 4, 5));
}

//#3: Variadic class templates
export void templates_3_demo(){

	//Creating a Bag with different types: Simple
	templates_3::simple::Bag<int, double, std::string> bag1(1, 3.14, "Hello");
	templates_3::simple::Bag<std::string, double, std::string> bag2("The sum is: ", 3.14, "Hello");

	fmt::println("\nSimple Bags: ");
	fmt::println("Bag1: {}, {}, {}", bag1.first, bag1.second, bag1.third);
	fmt::println("Bag2: {}, {}, {}", bag2.first, bag2.second, bag2.third);

	//We need a self expanding bag that can store any number of elements of different types.


	//Creating a Bag with different types: Wild
	templates_3::wild::Bag<int, double, std::string> bag3(1, 3.14, "Hello");
	templates_3::wild::Bag<std::string, double, std::string, int> bag4("The sum is: ", 3.14, "Hello", 42);

	//Printing bag3
	fmt::println("\nBag3: ");
	fmt::println("First value: {}", bag3.get_value());
	fmt::println("Second value: {}", bag3.get_tail().get_value());
	fmt::println("Third value: {}", bag3.get_tail().get_tail().get_value());

	//Printing bag4
	fmt::println("\nBag4: ");
	fmt::println("First value: {}", bag4.get_value());
	fmt::println("Second value: {}", bag4.get_tail().get_value());
	fmt::println("Third value: {}", bag4.get_tail().get_tail().get_value());
	fmt::println("Fourth value: {}", bag4.get_tail().get_tail().get_tail().get_value());
}



export void fold_expressions_demo(){
	//Trying out fold expressions
	//Unary left fold
	fmt::println("Unary left fold add 1,2,3: {}", fold_expressions::add_unary_left_fold(1, 2, 3));
	fmt::println("Unary left fold sub 1,2,3: {}", fold_expressions::sub_unary_left_fold(1, 2, 3));

	//Unary right fold
	fmt::println("Unary right fold add 1,2,3: {}", fold_expressions::add_unary_right_fold(1, 2, 3));
	fmt::println("Unary right fold sub 1,2,3: {}", fold_expressions::sub_unary_right_fold(1, 2, 3));

	//Binary left fold
	fmt::println("Binary left fold add 1,2,3: {}", fold_expressions::add_binary_left_fold(1, 2, 3));
	fmt::println("Binary left fold sub 1,2,3: {}", fold_expressions::sub_binary_left_fold(1, 2, 3));

	//Binary right fold
	fmt::println("Binary right fold add 1,2,3: {}", fold_expressions::add_binary_right_fold(1, 2, 3));
	fmt::println("Binary right fold sub 1,2,3: {}", fold_expressions::sub_binary_right_fold(1, 2, 3));


	//Trying out empty parameter packs
	//Unary folds must have at least one parameter, otherwise, you'll get a compiler error.
	//fmt::println("Unary left fold add: {}", fold_expressions::add_unary_left_fold()); Error
	//fmt::println("Unary right fold add: {}", fold_expressions::add_unary_right_fold()); Error
	//fmt::println("Binary left fold add: {}", fold_expressions::add_binary_left_fold()); 
	//fmt::println("Binary right fold add: {}", fold_expressions::add_binary_right_fold());
	//fmt::println("Unary left fold add 1: {}", fold_expressions::add_unary_left_fold(1));
}