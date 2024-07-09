module;

#include <string_view>
#include <fmt/format.h>
#include <iostream>

//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

import point;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

//#1: unary prefix operator+ as member
/*
export void unary_prefix_operator_as_member(){
	Point p1(10, 10);
	std::cout << "p1: " << p1 << "\n";

	// ++p1;
	p1.operator++();
	std::cout << "p1: " << p1 << "\n";

	for (size_t i{}; i < 20; ++i) {
		++p1;
		std::cout << "p1: " << p1 << "\n";
	}
}
*/

//#2: unary prefix operator+ done as non-member
/*
export void unary_prefix_plus_operator_as_non_member(){
	Point p1(10, 10);
	std::cout << "p1: " << p1 << "\n";

	//++p1;
	operator++(p1);
	std::cout << "p1: " << p1 << "\n";

	for (size_t i{}; i < 20; ++i) {
		++p1;
		std::cout << "p1: " << p1 << "\n";
	}
}
*/


//#3: post fix increment operator+
export void postfix_plus_operator(){
	Point p1(10, 10);
	auto p2 = p1++;
	std::cout << "p1: " << p1 << "\n";
	std::cout << "p2: " << p2 << "\n";
	std::cout << "p2++: " << p2++ << "\n";
}