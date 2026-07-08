#include <iostream>
#include "point.h"


int main(){
    Point point1(10.0,10.0);
	Point point2(20.0,20.0);
  
    std::cout << "point1 : " << point1 << std::endl;
	std::cout << "point2 : "  << point2 << std::endl;
	
   
    std::cout << "point1 > point2 : " <<std::boolalpha <<(point1 > point2) << std::endl;
    std::cout << "point1 < point2 : "  << (point1 < point2) << std::endl;
    std::cout << "point1 >= point2 : " << (point1 >= point2) << std::endl;
    std::cout << "point1 <= point2 : " << (point1 <= point2) << std::endl;
    std::cout << "point1 == point2 : " << (point1 ==point2) << std::endl;
    std::cout << "point1 != point2 : " << (point1 != point2) << std::endl;
 
    
    return 0;
}