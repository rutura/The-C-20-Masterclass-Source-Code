module;
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void print_number(int number) {
	fmt::println("value: {}",number);
}

// Marking a function as constexpr gives it the potential
// to be evaluated at compile time
/*
export constexpr int get_value(int multiplier) {
	return 3 * multiplier; 
}
*/


// Evaluate this function at compile time. If you can't
// do that throw a compiler error
export consteval int get_value(int multiplier) {
	 return 3 * multiplier; 
}