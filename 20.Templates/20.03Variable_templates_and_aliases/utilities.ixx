module;
#include <string_view>
#include <fmt/format.h>

export module utilities; 

import variable_templates;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void variable_templates_demo(){
	//Using function template
	fmt::println("Using function template");
	auto pi_float = variable_templates::pi<float>();
	auto pi_double = variable_templates::pi<double>();
	auto pi_long_double = variable_templates::pi<long double>();
	fmt::println("Pi: float: {}, double: {}, long double: {}", pi_float, pi_double, pi_long_double);

	//Using variable template
	fmt::println("Using variable template");
	auto pi_float_v = variable_templates::PI<float>;
	auto pi_double_v = variable_templates::PI<double>;
	auto pi_long_double_v = variable_templates::PI<long double>;
	fmt::println("Pi: float: {}, double: {}, long double: {}", pi_float_v, pi_double_v, pi_long_double_v);
}