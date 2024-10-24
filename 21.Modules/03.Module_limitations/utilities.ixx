module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import module_limitations_01;

/*
	Do's and don'ts
		. You can export: 
			. Variables, functions, classes, concepts, and templates.
		. You can't export entities with internal linkage, like names
			living in an anonymous namespaces, and those qualified with 
			the static keyword.
		. You can only export things that live at the namespace level. For example, 
			you can't export a class that's nested inside another class, or member
			variables of a class.
		. Template code should live in a single module file, separating into different
			interface files or implementation files will lead to weird errors (Personal experience)
*/

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
	//fmt::println("{}", my_add(str1, str2)); // The multipliable concept is not satisfied by the string type

	// Print the version from the math module
	fmt::println("Math version: {}", VERSION);
}