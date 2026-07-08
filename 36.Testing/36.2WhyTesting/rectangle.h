#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
public:
	Rectangle(double width, double height) : m_width{width}, m_height{height} {
	}

	double area() const {
		return m_width * m_height;
	}

	double perimeter() const {
		// Bug: should be 2 * (m_width + m_height)
		return 2 * m_width + m_height;
	}

private:
	double m_width{};
	double m_height{};
};

#endif // RECTANGLE_H
