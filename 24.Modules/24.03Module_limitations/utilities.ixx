module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import module_limitations_01;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


//Using exported concept
template <Multipliable T>
T my_add(T a, T b)
{
	return a + b;
}
export void module_limitations_01_demo(){

	//Add two numbers using my_add
	fmt::println("{}", my_add(1, 2));

	const char* str1{ "Hello" };
	const char* str2{ "World" };

	//Try to add two strings using my_add
	//fmt::println("{}", my_add(str1, str2));

	// Print the version from the math module
	fmt::println("Math version: {}", VERSION);
}