#include <fmt/format.h>
#include "point.h"

int main(){

//	fmt::println("{}" ,(Point(20,20) - Point(10,10)) );
//	fmt::println("{}" ,(Point(20,20) + Point(10,10)) );
	
    Point p1(10,10);
    Point p2(20,20);
    Point p3{p1 + p2};
    Point p4{p2 - Point(5,5)};
    
    fmt::println( "point1 : {}" ,  p1 ); // (10,10)
    fmt::println( "point3 : {}" , p3 ); // (30,30)
    fmt::println( "point4 : {}" , p4 ); // (15,15)

    return 0;
}