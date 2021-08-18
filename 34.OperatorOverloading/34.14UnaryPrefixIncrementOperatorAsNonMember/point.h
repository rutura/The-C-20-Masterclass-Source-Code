#ifndef POINT_H
#define POINT_H
#include <iostream>

class Number;


class Point
{
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
	friend void operator++(Point& operand);
	
public:
	Point() = default;
	Point(double x, double y) : 
		m_x(x), m_y(y){
	}

	/*
	void operator++() {
		++m_x;
		++m_y;
	}
	*/

	~Point() = default;

private: 
	double length() const;   // Function to calculate distance from the point(0,0)

private : 
	double m_x{}; 
	double m_y{}; 
};

/*
inline void operator++(Point& operand){
	++(operand.m_x);
	++(operand.m_y);
}
*/

inline std::ostream& operator<<(std::ostream& os, const Point& p){
	os << "Point [ x : " << p.m_x << ", y : " << p.m_y << "]";	
	return os;
}


#endif // POINT_H
