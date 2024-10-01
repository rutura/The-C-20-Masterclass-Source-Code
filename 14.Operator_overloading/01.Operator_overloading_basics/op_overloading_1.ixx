module;

#include <cmath>
#include <fmt/format.h>
#include <cassert>

export module op_overloading_1;

namespace op_overloading_1{

    //#1: Overload operator+ as a member
    export class Point
    {
    public:
    Point(double x, double y) : m_x(x), m_y(y) {}

    // Member
    //   Point operator+(const Point& right_operand){
    //       return Point(this->m_x + right_operand.m_x ,
    //                     this->m_y + right_operand.m_y );
    //   }

    Point operator+(const Point &right_operand);

    void print_info() { fmt::println("Point [ x: {}, y: {} ]", m_x, m_y); }

    private:
    double length() const;// Function to calculate distance from the point(0,0)

    private:
    double m_x{};
    double m_y{};
    };

    //Implementation

    double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

    Point Point::operator+(const Point &right_operand)
    {
    return Point(this->m_x + right_operand.m_x, this->m_y + right_operand.m_y);
    }
    
} // namespace op_overloading_1