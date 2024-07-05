module;
#include <string_view>
#include <fmt/format.h>


//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

import create_namespace;
import point;
import cylinder;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void create_namespace(){
	auto result = Adjust::div(12, 3);
	fmt::println("result: {}", result);
}

export void ns_x_multiple_files(){
	Geom::Point p1(10, 20);
	Geom::Point p2(3.4, 6.1);
	p1.print_info();
	p2.print_info();

	fmt::println("---");

	Geom::Cylinder c1(1.4, 10);
	fmt::println("c1.volume : {}", c1.volume());
}