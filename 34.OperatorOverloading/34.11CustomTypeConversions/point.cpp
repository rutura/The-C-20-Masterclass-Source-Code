#include <cmath>
#include "point.h"
#include "number.h"


/*
Point::Point(const Number& n) 
: Point(static_cast<double>(n.get_wrapped_int()) ,
        static_cast<double>(n.get_wrapped_int()))
{
    std::cout << "Using the Point constructor" << std::endl;
}
*/

double Point::length() const{
    return sqrt(pow(m_x - 0, 2) +  pow(m_y - 0, 2) * 1.0); 
}




