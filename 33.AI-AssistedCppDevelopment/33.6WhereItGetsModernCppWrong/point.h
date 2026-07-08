#ifndef POINT_H
#define POINT_H

#include <compare>

// A prompt like "add comparison operators to this class" will often
// generate all six relational operators by hand (==, !=, <, <=, >, >=),
// because that pattern shows up constantly in pre-C++20 training data. It
// compiles and it works -- but it's six functions doing what one
// defaulted <=> already covers, and it's exactly the kind of "technically
// correct, but not how you'd write it today" suggestion this chapter is
// about catching. Chapter 19 (OperatorOverloading) already covered this.
class Point
{
public:
	Point(double x, double y) : m_x{x}, m_y{y} {
	}

	double x() const { return m_x; }
	double y() const { return m_y; }

	// The one line an AI assistant trained mostly on older code is prone to
	// skip in favor of six hand-written operators:
	auto operator<=>(const Point&) const = default;
	bool operator==(const Point&) const = default;

private:
	double m_x{};
	double m_y{};
};

#endif // POINT_H
