module;

#include <string_view>
#include <fmt/format.h>

export module utilities; // Name doesn't have to match the .ixx file

import template_basics;
import class_template_basics;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void function_template_basics_demo(){

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

export void class_template_basics_demo(){

	//Points made up of int
	class_template_basics::Point<int> p1(1, 2);
	class_template_basics::Point<int> p2(3, 4);
	auto p3 = p1 + p2;
	fmt::print("The point is: ({}, {})\n", p3.get_x(), p3.get_y());


	//Points made up of double
	class_template_basics::Point<double> p4(1.1, 2.2);
	class_template_basics::Point<double> p5(3.3, 4.4);
	auto p6 = p4 + p5;
	fmt::print("The point is: ({}, {})\n", p6.get_x(), p6.get_y());

	//Custom integers
	class_template_basics::Point<template_basics::Integer> p7(template_basics::Integer(10), template_basics::Integer(20));
	class_template_basics::Point<template_basics::Integer> p8(template_basics::Integer(30), template_basics::Integer(40));
	auto p9 = p7 + p8;
	fmt::print("The point is: ({}, {})\n", p9.get_x().get(), p9.get_y().get());
}