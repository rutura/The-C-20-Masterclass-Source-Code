module;
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives

import point;
import cylinder;

export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

// #1: Static members
/*
export void static_members(){
	// Print the point count in our program
	//    fmt::println( "Point count : {}" , Point::m_point_count ); //0

	Point p1(10.0, 20.1);
	fmt::println("Point count : {}", p1.get_point_count());// 1

	Point points[]{ Point(1, 1), Point(), Point(4) };
	fmt::println("Point count : {}", p1.get_point_count());// 4
}
*/


// #2: Inline static members
/*
export void inline_static_members(){

	// Print the point count in our program
	// fmt::println( "Point count : " , Point::m_point_count ); //0

	Point p1(10.0, 20.1);

	fmt::println("Point count : {}", p1.get_point_count());// 1

	Point points[]{ Point(1, 1), Point(), Point(4) };

	fmt::println("Point count : {}", p1.get_point_count());// 4
}
*/


// #3: Static constants
/*
export void static_constants(){
	Cylinder cylinder1(3.3, 10.0);
	fmt::println("Volume of cylinder : {}", cylinder1.volume());
	fmt::println("Cylinder default color : {}", Cylinder::default_color);
	fmt::println("Cylinder default color : {}", cylinder1.default_color);
}
*/


// #4: Static member functions
export void static_member_functions(){
	fmt::println( "Point count : {}" , Point::get_point_count() );
	Point p1{ 6, 7 };
	 fmt::println( "Point count : {}" , p1.get_point_count() );
	p1.print_info(p1);
}