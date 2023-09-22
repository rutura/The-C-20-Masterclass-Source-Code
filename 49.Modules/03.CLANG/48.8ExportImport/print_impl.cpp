module;
#include <cstring> // C function includes must show up here
module print;

import <iostream>;

//Implementations
void greet() {
	// std::string dest;
	// dest = "Hello ";
	// dest.append(name);
	std::cout << "Hello John" << std::endl;
}

void print_name_length(const char* c_str_name) {
	std::cout << "Length : " << std::strlen(c_str_name) << std::endl;
}