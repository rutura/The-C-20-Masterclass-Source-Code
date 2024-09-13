module;

#include <string_view>
//#include <iostream>
#include <fmt/format.h>

//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
	//std::cout << msg << std::endl;
}