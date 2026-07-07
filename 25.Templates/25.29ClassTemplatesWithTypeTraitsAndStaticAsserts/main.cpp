#include <iostream>
#include <type_traits>
#include "boxcontainer.h"

template <typename T>
class Point{
	    static_assert(std::is_arithmetic_v<T>,
        "Coordinates of Point can only be numbers.");
public : 
	Point() = default;
	Point(T x, T y)  
	: m_x(x), m_y(y)
	{
	}
	friend std::ostream& operator<< ( std::ostream& out, const Point<T> operand){
		out << "Point [ x : " << operand.m_x
					<< ", y : " << operand.m_y << "]";
		return out;
	}
private : 
	T m_x;
	T m_y;
};



int main(){

	Point<int> point_int(10,20);
	std::cout << "point_int : " << point_int << std::endl;
	
	Point<double> point_double(11.1,12.2);
	std::cout << "point_double : " << point_double << std::endl;

    /*
	Point<std::string> point_string("Hello","World");
    std::cout << "point_string : " << point_string << std::endl;
    */


	BoxContainer<Point<int>> point_box;
	point_box.add(point_int);
	point_box.add(Point<int>(40,50));
	
	std::cout << "point_box : " << point_box << std::endl;



    return 0;
}