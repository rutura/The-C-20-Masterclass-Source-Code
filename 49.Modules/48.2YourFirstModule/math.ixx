module;
// Global module fragment
#include <cstring> // C function includes must show up here
#include <string>
#include <fmt/format.h>

export module math_stuff; // Module declaration
//Module preamble
import <iostream>;

//Module purview
export double add(double a, double b) {
	return a + b;
}

export void greet(const std::string& name) {
	std::string dest;
	dest = "Hello ";
	dest.append(name);
	fmt::println( "{}", dest);
}

export void print_name_length(const char* c_str_name) {
	fmt::println("Length : {}",std::strlen(c_str_name));
}