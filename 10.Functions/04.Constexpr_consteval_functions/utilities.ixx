module;
#include <string_view>
#include <fmt/format.h>

export module utilities; 

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