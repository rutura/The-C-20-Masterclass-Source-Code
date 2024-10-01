module;

#include <iostream>
#include <cmath>

export module fix_ops_4;

namespace fix_ops_4{

    //Unary postfix operator+ as a non-member
    //#1: unary prefix operator+ as member

    export class Point
    {
    friend std::ostream &operator<<(std::ostream &os, const Point &p);
    friend void operator++(Point &operand);
    friend Point operator++(Point &operand, int);

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


    //Implementation
    double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

    //Prefix operator+ done as a non-member
    inline void operator++(Point& operand){
        ++(operand.m_x);
        ++(operand.m_y);
    }

    //Postfix operator++ done as non-member. In terms of prefix operator
    Point operator++(Point &operand, int)
    {
        Point local_point(operand);
        ++operand;
        return local_point;
    }
    
} // namespace fix_ops_4