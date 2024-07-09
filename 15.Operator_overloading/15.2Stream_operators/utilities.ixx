module;
#include <string_view>
#include <iostream>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

import point;

//Module purview
export void print_msg(std::string_view msg) {
	//fmt::println("{}",msg);
}


//#1: Overloading the stream insertion operator 
export void overload_stream_insertion_operator(){
	Point p1(10, 20);
	Point p2(3, 4);

	std::cout << p1 << "\n";
	std::cout << p2 << "\n";

}

//#2: Overloading the stream extraction operator
export void overload_stream_extraction_operator(){
	Point p2;
	std::cin >> p2;//
	std::cout << p2 << "\n";
}