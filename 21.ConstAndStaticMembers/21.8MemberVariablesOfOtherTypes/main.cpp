#include <iostream>
#include "point.h"

int main(){

	std::cout << std::endl;
	std::cout << "Entering main: " << std::endl;
	
	Point point1(3.0,3.0);
	std::cout << "distance : " << point1.length() << std::endl;
	
	std::cout << std::endl;
	std::cout << "Reading in the integers " << std::endl;
	
	std::cout << "point1.i1 : " << point1.i1.get_value() << std::endl;
	std::cout << "point1.i2 : " << point1.i2.get_value() << std::endl;
	std::cout << "Point::i3 : " << Point::i3.get_value() << std::endl;
	std::cout << "Point::i4 : " << Point::i4.get_value() << std::endl;

	
	//point1.i1.set_value(8);// Works, i1 is not const
	//point1.i2.set_value(10); // Compiler error, i2 is const, can't modify it.
	
	std::cout << "point1.p_i5 (pointer) : " << point1.p_i5->get_value() << std::endl;
	
	std::cout << "Point::i6 : " << Point::i6.get_value() << std::endl;
	std::cout << "Point::i7 : " << Point::i7.get_value() << std::endl;
	
	//Point::i6.set_value(50);
	//Point::i7.set_value(60); // Compiler error : i6 is const.
	
	std::cout << std::endl;
	std::cout << "Leaving main" << std::endl;
 
    return 0;
}