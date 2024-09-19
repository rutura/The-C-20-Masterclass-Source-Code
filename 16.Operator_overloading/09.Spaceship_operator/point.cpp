#include "point.h"



std::ostream &operator<<(std::ostream &out, const Point &p)
{
  out << "Point [ x : " << p.m_x << ", y : " << p.m_y << " length : " << p.length() << "]";
  return out;
}

//Implementations

double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

bool Point::operator==(const Point &other) const { return (this->length() == other.length()); }

/*
bool Point::operator!=(const Point& other) const{
    return !(*this ==  other);
}
*/