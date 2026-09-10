#include <cmath>
#include "point.h"


double Point::length() const{
    return sqrt(pow(m_x - 0, 2) +  pow(m_y - 0, 2) * 1.0); 
}


void operator++(Point& operand){
	++(operand.m_x);
	++(operand.m_y);
}

Point operator++(Point& operand,int){
	Point local_point(operand);
	++operand;
	return local_point;
}





