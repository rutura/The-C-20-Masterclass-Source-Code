#include <iostream>
#include "point.h"


int main(){

   // std::cout << "Point count : " << Point::get_point_count() << std::endl;

    Point p1{6,7};

   // std::cout << "Point count : " << p1.get_point_count() << std::endl;
    p1.print_info(p1) ;

 
    return 0;
}