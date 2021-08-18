#include <iostream>
#include "point.h"


int main(){

    Point p1(10,10);
    Point p2(20,20);
    //Point p3{p1 + p2}; // opearator+(p1,p2);
    Point p3{operator+ (p1,p2)};

    Point p4{p2 + Point(5,5)};
    
    p3.print_info();
    p4.print_info();

    (Point(20,20) + Point(10,10)).print_info();
    
    return 0;
}