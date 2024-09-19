#include "utilities.h"

#include <fmt/format.h>
#include "point.h"

void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

// #1: Static members
/*
void static_members(){
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
void inline_static_members(){

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
void static_constants(){
	Cylinder cylinder1(3.3, 10.0);
	fmt::println("Volume of cylinder : {}", cylinder1.volume());
	fmt::println("Cylinder default color : {}", Cylinder::default_color);
	fmt::println("Cylinder default color : {}", cylinder1.default_color);
}
*/


// #4: Static member functions
void static_member_functions(){
	fmt::println( "Point count : {}" , Point::get_point_count() );
	Point p1{ 6, 7 };
	 fmt::println( "Point count : {}" , p1.get_point_count() );
	p1.print_info(p1);
}