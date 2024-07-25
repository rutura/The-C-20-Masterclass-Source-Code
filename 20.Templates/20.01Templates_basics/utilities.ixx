module;

#include <string_view>
#include <fmt/format.h>

export module utilities; // Name doesn't have to match the .ixx file

import template_basics;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void template_basics_demo(){

	auto value = template_basics::add(1,2);
	fmt::print("The value is: {}\n", value);

	template_basics::Integer a(1);
	template_basics::Integer b(2);
	auto sum = a + b;
	fmt::print("The sum is: {}\n", sum.get());

	auto result = template_basics::add(11.1, 22.2);
	fmt::print("The result is: {}\n", result);

	std::string lastname = "Doe";
	std::string firstname = "John";
	auto fullname = template_basics::add(firstname, lastname);
	fmt::print("The full name is: {}\n", fullname);


	template_basics::Point p1(1.1, 2.2);
	template_basics::Point p2(3.3, 4.4);
	auto p3 = p1 + p2;
	fmt::print("The point is: ({}, {})\n", p3.get_x(), p3.get_y());

}