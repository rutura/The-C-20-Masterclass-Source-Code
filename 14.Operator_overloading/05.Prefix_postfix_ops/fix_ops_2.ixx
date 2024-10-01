module;

#include <iostream>
#include <cmath>

export module fix_ops_2;

namespace fix_ops_2{

    //Unary prefix operator+ as non-member
    export class Point
    {
    friend std::ostream &operator<<(std::ostream &os, const Point &p);
    friend void operator++(Point &operand);

    public:
    Point(double x, double y) : m_x(x), m_y(y) {}

    private:
    double length() const;// Function to calculate distance from the point(0,0)

    private:
    double m_x{};
    double m_y{};
    };

    inline std::ostream &operator<<(std::ostream &os, const Point &p)
    {
    os << "Point [ x: " << p.m_x << ", y: " << p.m_y << "]";
    return os;
    }

    //Unary prefix operator+ done as a non-member
    inline void operator++(Point& operand){
            ++(operand.m_x);
            ++(operand.m_y);
    }


    //Implementation
    double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

} // namespace fix_ops_2