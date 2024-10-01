module;

#include <string_view>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import fix_ops_1;
import fix_ops_2;
import fix_ops_3;
import fix_ops_4;


//#1: unary prefix operator+ as member
export void fix_ops_1_demo(){
	fix_ops_1::Point p1(10, 10);
	std::cout << "p1: " << p1 << "\n";
	++p1;
	p1.operator++();
	std::cout << "p1: " << p1 << "\n";
}

//#2: unary prefix operator+ done as non-member
export void fix_ops_2_demo(){
	fix_ops_2::Point p1(10, 10);
	std::cout << "p1: " << p1 << "\n";
	++p1;
	operator++(p1);
	std::cout << "p1: " << p1 << "\n";
}

//Unary postfix operator+ as member
export void fix_ops_3_demo(){
	fix_ops_3::Point p1(10, 10);
	std::cout << "p1: " << p1++ << "\n";
	std::cout << "p1: " << p1 << "\n";
}

export void fix_ops_4_demo(){
	fix_ops_4::Point p1(10, 10);
	std::cout << "p1: " << p1++ << "\n";
	std::cout << "p1: " << p1 << "\n";
}