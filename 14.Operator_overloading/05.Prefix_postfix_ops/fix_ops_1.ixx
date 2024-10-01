module;

#include <iostream>
#include <cmath>

export module fix_ops_1;

namespace fix_ops_1{

    //Unary prefix operator+ as member
    export class Point
    {
    friend std::ostream &operator<<(std::ostream &os, const Point &p);

    public:
    Point(double x, double y) : m_x(x), m_y(y) {}

    //prefix operator done as a member
    void operator++()
    {
        ++m_x;
        ++m_y;
    }

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

    //Implementation
    double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

} // namespace fix_ops_1