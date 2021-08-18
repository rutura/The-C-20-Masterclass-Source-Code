#ifndef POINT_H
#define POINT_H
#include <iostream>


class Point
{
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
	friend std::istream& operator>>(std::istream& is, Point& p);
public:
	Point() = default;
	Point(double x, double y) : 
		m_x(x), m_y(y){
	}
	~Point() = default;

	void print_info(){
		std::cout << "Point [ x : " << m_x << ", y : " << m_y << "]" << std::endl;
	}

	/*
	std::ostream& operator<< (std::ostream& os){
		os << "Point [ x : " << m_x << ", y : " << m_y << "]";
		return os;			
	}
	*/

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

inline std::istream& operator>>(std::istream& is, Point& p){
	double x;
	double y;

    std::cout << "Please type in the coordinates for the point" << std::endl;
    std::cout << "order [x,y], separated by spaces : ";

	is >> x >> y ;
	p.m_x = x;
	p.m_y = y;

	return is;
}

#endif // POINT_H
