module;
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

import op_overloading_1;
import op_overloading_2;
import op_overloading_3;
import op_overloading_4;
import op_overloading_5;
import op_overloading_6;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


//#1: Overloading the + operator as a member
export void op_overloading_1_demo(){

	op_overloading_1::Point p1(10, 10);
	op_overloading_1::Point p2(20, 20);
	op_overloading_1::Point p3{ p1 + p2 };// p1.operator+(p2)
	p3.print_info();

}



//#2: Overload operator+ as a non member
export void op_overloading_2_demo(){
	op_overloading_2::Point p1(10, 10);
	op_overloading_2::Point p2(20, 20);
	op_overloading_2::Point p3{ p1 + p2 };// operator+(p1,p2)
	p3.print_info();
}


//#3: Overload the subscript operator
export void op_overloading_3_demo(){
	op_overloading_3::Point p1(10, 20);
	fmt::println( "p1.x : {}" , p1[0] ); // x coordinate : 10
	fmt::println("p1.x : {}", p1.operator[](0));// x coordinate : 10
	fmt::println("p1.y : {}", p1[1]);// y coordinate : 20

}

//#4: Overload the subscript operator for reading and writting
export void op_overloading_4_demo(){
	op_overloading_4::Point p1(10, 20);
	p1.print_info();

	// Changing the data
	p1[0] = 35.6;
	p1[1] = 23.9;
	p1.print_info();
}

//#5: Subscript operator for collection types
export void op_overloading_5_demo(){
	op_overloading_5::Scores math("Math");
	math.print_info();

	for (size_t i{}; i < 20; ++i) {
		if (i == 0) {
		math[0] = 73.7;
		} else {
		math[i] = math[i - 1] + 0.56;
		}
	}

	math.print_info();

	fmt::println("------");
	// Const objecst
	const op_overloading_5::Scores geo("Geography");
	fmt::println("geo [5] : {}", geo[5]);
}


export void op_overloading_6_demo(){
    op_overloading_6::Array3d v;
    v[3, 2, 1] = 42;
	fmt::print("v[3,2,1] = {}\n", v[3, 2, 1]);
}