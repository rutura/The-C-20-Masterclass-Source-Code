module;
#include <string_view>
#include <fmt/format.h>

import dog;

//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void getters_as_setters(){
	const Dog dog1("Fluffy", "Shepherd", 2);
	dog1.print_info();
	fmt::println("dog name : {}", dog1.name());// Getter

	// Modify the object
	// dog1.name() = "Milou"; // Setter
	dog1.print_info();
}