module;
#include <iostream>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

import point;

//Module purview

export void use_point(){
	Point p(10,10);
	auto distance = p.distance_from_origin();
	std::cout << "distance: " << distance <<  "\n";
}