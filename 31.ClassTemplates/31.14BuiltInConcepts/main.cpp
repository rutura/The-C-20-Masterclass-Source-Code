#include <iostream>
#include <concepts>
#include "boxcontainer.h"

template <typename T>
requires std::is_arithmetic_v<T>
class Point{
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
	std::weak_ordering operator<=>(const Point& other) const = default;
private : 
	T m_x;
	T m_y;
};

struct  Dog
{
	~Dog() = delete;
};

struct  Cat
{
};




int main(){

	//Numbers
	//std::floating_point<T>
	//static_assert(std::floating_point<int>);//Fails
	//static_assert(std::floating_point<double>);

	//equality and order
	//https://en.cppreference.com/w/cpp/concepts/equality_comparable
	//static_assert(std::equality_comparable<int>); // == , !=
	//static_assert(std::equality_comparable_with<double,std::string>);

	//static_assert(std::totally_ordered<int>);
	//static_assert(std::totally_ordered<Point<int>>); // Needs all comparison operators



	//Others
	//std::same_as
	//static_assert(std::same_as<int,int>); // Success
	//static_assert(std::same_as<int,double>);// Fail
	//static_assert(std::same_as<Dog,Cat>); //Fail
	//static_assert(std::same_as<BoxContainer<int>, BoxContainer<int>>); // Success
	//static_assert(std::same_as<BoxContainer<int>, BoxContainer<double>>); // Fail
	//static_assert(std::same_as<Point<int>,Point<int>>); // Success
	//static_assert(std::same_as<Point<int>,Point<float>>); // Fail
	

	//std::destructible
	//static_assert(std::destructible<Dog>);
	//std::derived_from : See official example  : https://en.cppreference.com/w/cpp/concepts/derived_from

	//std::copyable : needs a copy constructor
	//And much more

    return 0;
}