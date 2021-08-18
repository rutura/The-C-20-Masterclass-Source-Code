#include <cmath>
#include "point.h"

double Point::length() const{
    return sqrt(pow(m_x - 0, 2) +  pow(m_y - 0, 2) * 1.0); 
}

bool Point::operator==(const Point& other) const{
    return (this->length() == other.length());
}

std::partial_ordering Point::operator<=>(const Point& right) const{
	if(length() > right.length())
		return std::partial_ordering::greater;
	else if(length() == right.length())
		return std::partial_ordering::equivalent;
	else if(length() < right.length())
		return std::partial_ordering::less;
	else
		return std::partial_ordering::unordered;
}



