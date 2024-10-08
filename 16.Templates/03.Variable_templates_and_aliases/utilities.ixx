module;
#include <string_view>
#include <fmt/format.h>

export module utilities; 

import templates_1;
import templates_2;

//#1: Variable templates
export void templates_1_demo(){
	using templates_1::PI;

	//Using variable template
	fmt::println("Using variable template");
	auto pi_float_v = PI<float>;
	auto pi_double_v = PI<double>;
	auto pi_long_double_v = PI<long double>;
	fmt::println("PI<float>: {}", pi_float_v);
	fmt::println("PI<double>: {}", pi_double_v);
	fmt::println("PI<long double>: {}", pi_long_double_v);

	//Checking integers
	templates_1::check_integer();

	//Printing default values
	templates_1::print_default_values();

	//Printing factorial computed at compile-time
	fmt::println("Factorial of 5: {}", templates_1::factorial<5>);
}


//#2: Alias templates
export void templates_2_demo(){
	
	using templates_2::KeyValueStore;
	using templates_2::Vec;
	using templates_2::StringKeyStore;

	fmt::println("Using alias templates: ");
	Vec<int> vec{1,2,3,4,5};
	for(const auto& elem: vec){
		fmt::print("{} ", elem);
	}
	fmt::print("\n");

	StringKeyStore<int> store;
	store.insert("one", 1);
	store.insert("two", 2);
	store.insert("three", 3);
	fmt::println("Value of one: {}", store.get("one"));
	fmt::println("Value of two: {}", store.get("two"));
	fmt::println("Value of three: {}", store.get("three"));
}