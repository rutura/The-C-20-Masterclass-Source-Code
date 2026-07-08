#ifndef POINT_H
#define POINT_H
#include <compare>
#include <format>
#include <string>

class Point
{
public:
	Point() = default;
	Point(double x, double y) :
		m_x(x), m_y(y){
	}
	//Operators
    bool operator==(const Point& other) const;
	std::partial_ordering operator<=>(const Point& right) const;

	double length() const;   // Function to calculate distance from the point(0,0)

public :
	double m_x{};
	double m_y{};
};

// std::print/std::format need a std::formatter specialization to know how
// to render a custom type - there's no automatic fallback to operator<<.
template <>
struct std::formatter<Point> : std::formatter<std::string> {
	auto format(const Point& p, std::format_context& ctx) const {
		return std::formatter<std::string>::format(
			std::format("Point [ x : {}, y : {}, length : {} ]", p.m_x, p.m_y, p.length()), ctx);
	}
};

#endif // POINT_H
