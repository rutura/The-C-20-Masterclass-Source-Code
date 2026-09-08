module;
#include <cstring> // C function includes must show up here
#include <string>
module print;

import <iostream>;


//Implementations
void greet() {
	std::cout << "Hello John" << std::endl;
}

void print_name_length(const char* c_str_name) {
	std::cout << "Length : " << std::strlen(c_str_name) << std::endl;
}