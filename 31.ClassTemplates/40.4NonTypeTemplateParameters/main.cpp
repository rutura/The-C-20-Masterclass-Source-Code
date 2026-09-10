#include <iostream>
#include "boxcontainer.h"

template <typename T, T threashold>
class Point{
public : 
	Point(T x , T y);
	~Point() = default;
private : 
	T m_x;
	T m_y;
};

template <typename T, T threashold>
Point<T,threashold>::Point(T x, T y)
	: m_x(x) , m_y(y)
{
		
}



int main(){

    /*
	BoxContainer<int,5> int_box1; // One instance
	BoxContainer<int,10> int_box2; // Another instance
	*/
   

	 Point<int,44> point1(10,20); // Works
    //Point<double,33.1> point2(11.22,22.33);// Compiler error : double not a valid
											// non type template parameter : only integral types
											//that can represent sizes or ranges allowed.
	
    return 0;
}