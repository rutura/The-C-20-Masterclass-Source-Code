#include <fmt/format.h>
#include "point.h"

int main(){

	fmt::println("\n");
	fmt::println( "Entering main: " );
	
	Point point1(3.0,3.0);
	fmt::println( "distance : {}" , point1.length() );
	
	fmt::println("\n");
	fmt::println( "Reading in the integers " );
	
	fmt::println( "point1.i1 : {}" , point1.i1.get_value() );
	fmt::println( "point1.i2 : {}" , point1.i2.get_value() );
	fmt::println( "Point::i3 : {}" , Point::i3.get_value() );
	fmt::println( "Point::i4 : {}" , Point::i4.get_value() );

	
	//point1.i1.set_value(8);// Works, i1 is not const
	//point1.i2.set_value(10); // Compiler error, i2 is const, can't modify it.
	
	fmt::println( "point1.p_i5 (pointer) : {}" , point1.p_i5->get_value() );
	
	fmt::println( "Point::i6 : {}" , Point::i6.get_value() );
	fmt::println( "Point::i7 : {}" , Point::i7.get_value() );
	
	//Point::i6.set_value(50);
	//Point::i7.set_value(60); // Compiler error : i6 is const.
	
	fmt::println("\n");
	fmt::println( "Leaving main" );
 
    return 0;
}