#ifndef POINT_H
#define POINT_H
#include <fmt/format.h>

class Point
{
	friend std::ostream& operator<< (std::ostream& out , const Point& p);
public:
	Point() = default;
	Point(double x, double y) : 
		m_x{x}, m_y{y}{}

	Point(double x_y) : Point{x_y,x_y}{}
	//Operators
    bool operator==(const Point& other) const;
	std::partial_ordering operator<=>(const Point& right) const;
double x() const {
	return m_x;
}
	double y() const {
	return m_y;
}
	double length() const;   // Function to calculate distance from the point(0,0)
private:
	double m_x{};
	double m_y{};
};

inline std::ostream& operator<< (std::ostream& out , const Point& p){
	out << "Point [ x : " << p.m_x << ", y : " << p.m_y <<
       " length : " << p.length()  <<  "]" ;
	return out;
}
/*
 - fmt output stream overloading for Point of double
 - Reference: https://fmt.dev/latest/api.html
 */
template <>
struct fmt::formatter<Point> : nested_formatter<double> {
	auto format(Point p, format_context& ctx) const {
		return write_padded(ctx, [=](auto out) {
		  return format_to(out, "Point [ x: {}, y: {}, length: {}]", nested(p.x()), nested(p.y()), nested(p.length()));
		});
	}
};



#endif // POINT_H
