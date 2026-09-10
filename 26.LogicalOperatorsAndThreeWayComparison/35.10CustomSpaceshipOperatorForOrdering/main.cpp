#include <iostream>
#include "point.h"

int main(){

    Point point1(10.0,10.0);
	Point point2(20.0,20.0);
    std::cout << "point1 : " << point1 << std::endl;
    std::cout << "point2 : " << point2 << std::endl;
  

    std::cout << std::boolalpha;
    auto result1 = (point1 > point2);
    std::cout << "point1 > point2 : " << result1 << std::endl;

    auto result2 = (point1 >= point2);
    std::cout << "point1 >= point2 : " << result2 << std::endl;

    auto result3 = (point1 == point2);
    std::cout << "point1 == point2 : " << result3 << std::endl;

    auto result4 = (point1 != point2);
    std::cout << "point1 != point2 : " << result4 << std::endl;

    auto result5 = (point1 < point2);
    std::cout << "point1 < point2 : " << result5 << std::endl;

    auto result6 = (point1 <= point2);
    std::cout << "point1 <= point2 : " << result6 << std::endl;


    //Implicit conversions
    std::cout << "point1 > 20.1 : " << (point1 > 20.1) << std::endl;
    //std::cout << "20.1 > point1 : " << (20.1 > point1) << std::endl;
    std::cout << "20.1 > point1 : " << ((point1 <=> 20.1) < 0) << std::endl;
    //((point1 <=> 20.1) < 0)

   
    return 0;
}