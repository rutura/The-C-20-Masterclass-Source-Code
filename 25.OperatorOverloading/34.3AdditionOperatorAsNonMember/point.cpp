#include <cmath>
#include "point.h"

double Point::length() const{
    return sqrt(pow(m_x - 0, 2) +  pow(m_y - 0, 2) * 1.0); 
}

/*
Point operator+(const Point& left, const Point& right){
	return Point(left.m_x + right.m_x , left.m_y + right.m_y );
}
*/

