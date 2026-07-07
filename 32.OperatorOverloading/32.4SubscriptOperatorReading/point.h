#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cassert>

class Point
{
public:
	Point() = default;
	Point(double x, double y) : 
		m_x(x), m_y(y){
	}
	~Point() = default;

	double operator[](size_t index) const{
		assert( (index == 0) || (index == 1));
		if(index == 0){
			return m_x;
		}else{
			return m_y;
		}
	}

	void print_info(){
		std::cout << "Point [ x : " << m_x << ", y : " << m_y << "]" << std::endl;
	}
private: 
	double length() const;   // Function to calculate distance from the point(0,0)

private : 
	double m_x{}; // 0
	double m_y{}; // 1
};

#endif // POINT_H
