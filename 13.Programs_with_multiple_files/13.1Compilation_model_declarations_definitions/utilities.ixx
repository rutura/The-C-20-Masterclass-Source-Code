module;
#include <iostream>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

import point;
import person;

//Module purview

//Declarations and definitions
double weight;

// Functions : Declaration and defintion
double add(double a, double b){
    return a + b;
}

// Declaration
//double add(double a, double b);


// Declaration and definition
struct D_Vector
{
  double m_x;
  double m_y;
};

//Trigger ODR
/*
struct Point{
	
};
*/

export void use_point(){
	Point p(10,10);
	auto distance = p.distance_from_origin();
	std::cout << "distance: " << distance <<  "\n";
}

export void use_person(){
	weight = 5; // Assignment

	std::cout << weight << "\n";

	double result = add(10,20.5);
	std::cout << "result: " << result << "\n";

	Person p1("John Snow", 27);
	p1.print_info();
}