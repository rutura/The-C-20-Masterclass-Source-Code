module;

#include <iostream>
#include <string_view>
#include <fmt/format.h>

export module utilities; 

import point;
import number;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void logical_operators(){
	Point point1(10.0, 10.0);
	Point point2(20.0, 20.0);

	std::cout << "point1: " << point1 << "\n";
	std::cout << "point2: " << point2 << "\n";


	fmt::println("point1 > point2 : {}", (point1 > point2));
	fmt::println("point1 < point2 : {}", (point1 < point2));
	fmt::println("point1 >= point2 : {}", (point1 >= point2));
	fmt::println("point1 <= point2 : {}", (point1 <= point2));
	fmt::println("point1 == point2 : {}", (point1 == point2));
	fmt::println("point1 != point2 : {}", (point1 != point2));
}

export void logical_ops_implicit_conversions(){
	Number n1(10);
	Number n2(20);

	fmt::println("n1 < n2 : {}", (n1 < n2));
	fmt::println("15 < n2 : {}", (15 < n2));
	fmt::println("n1 < 25 : {}", (n1 < 5));
}