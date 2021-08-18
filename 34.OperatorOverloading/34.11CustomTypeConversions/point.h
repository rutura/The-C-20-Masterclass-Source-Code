#ifndef POINT_H
#define POINT_H
#include <iostream>

class Number;


class Point
{
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
	friend Point operator+(const Point& left , const Point& right);
	friend Point operator-(const Point& left , const Point& right);
	friend Point& operator+=(Point& left, const Point& right);
	friend Point& operator-=(Point& left, const Point& right);
	
public:
	Point() = default;
	Point(double x, double y) : 
		m_x(x), m_y(y){
	}
	/*
	explicit Point(const Number& n);
	*/
	~Point() = default;

	void print_info(){
		std::cout << "Point [ x : " << m_x << ", y : " << m_y << "]" << std::endl;
	}

private: 
	double length() const;   // Function to calculate distance from the point(0,0)

private : 
	double m_x{}; 
	double m_y{}; 
};

inline std::ostream& operator<<(std::ostream& os, const Point& p){
	os << "Point [ x : " << p.m_x << ", y : " << p.m_y << "]";	
	return os;
}

inline Point& operator+=(Point& left, const Point& right){
	left.m_x += right.m_x;
	left.m_y += right.m_y;
	return left;
}

inline Point& operator-=(Point& left, const Point& right){
	left.m_x -= right.m_x;
	left.m_y -= right.m_y;
	return left;
}


inline Point operator+(const Point& left , const Point& right){
	Point p(left);
	return p+=right;
}

inline Point operator-(const Point& left , const Point& right){
	Point p(left);
	return p-=right;
}


#endif // POINT_H
