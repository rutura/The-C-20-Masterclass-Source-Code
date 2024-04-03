#ifndef POINT_H
#define POINT_H
#include <iostream>

class Number;


class Point
{
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
	friend void operator++(Point& operand);
	friend struct fmt::formatter<Point>;
public:
	Point() = default;
	Point(double x, double y) : 
		m_x(x), m_y(y){
	}
	/*
	//Prefix
	void operator++() {
		++m_x;
		++m_y;
	}


	//Postfix
	Point operator++(int){
		Point local_point(*this);
		++(*this);
		return local_point;
	}
	*/

	

	~Point() = default;

private: 
	double length() const;   // Function to calculate distance from the point(0,0)

private : 
	double m_x{}; 
	double m_y{}; 
};
Point operator++(Point& operand,int);


inline std::ostream& operator<<(std::ostream& os, const Point& p){
	os << "Point [ x : " << p.m_x << ", y : " << p.m_y << "]";	
	return os;
}

template<>
struct fmt::formatter<Point>
{
  constexpr auto parse(format_parse_context& ctx){ return ctx.begin(); }
  template<typename FormatContext>
  auto format(const Point& obj, FormatContext& ctx){
    return format_to(ctx.out(), "Point [x: {}, y: {}]",obj.m_x, obj.m_y);
  }
};


#endif // POINT_H
