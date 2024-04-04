module;
#include <cstring> // C function includes must show up here
#include <fmt/format.h>

module print;

// import <iostream>;


//Implementations
void greet() {
	fmt::println( "Hello John");
	// std::cout << "Hello John" << std::endl;
}

void print_name_length(const char* c_str_name) {
	fmt::println("Length : {}",  std::strlen(c_str_name));
	// std::cout << "Length : " << std::strlen(c_str_name) << std::endl;
}