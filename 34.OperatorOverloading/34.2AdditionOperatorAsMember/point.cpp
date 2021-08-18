#include <cmath>
#include "point.h"

double Point::length() const{
    return sqrt(pow(m_x - 0, 2) +  pow(m_y - 0, 2) * 1.0); 
}

Point Point::operator+(const Point& right_operand){
    return Point(this->m_x + right_operand.m_x ,
                 this->m_y + right_operand.m_y );
}