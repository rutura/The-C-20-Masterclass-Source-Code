module;

#include <cmath>
#include <fmt/format.h>

export module op_overloading_2;

namespace op_overloading_2{

    //#2: Overload operator+ as a non_member
    export class Point
    {
    friend Point operator+(const Point &left, const Point &right);
    public:
    Point(double x, double y) : m_x(x), m_y(y) {}

    void print_info() { fmt::println("Point [ x : {}, y: {}s]", m_x, m_y); }

    private:
    double length() const;// Function to calculate distance from the point(0,0)

    private:
    double m_x{};
    double m_y{};
    };


    // inline Point operator+(const Point &left, const Point &right)
    // {
    //   return Point(left.m_x + right.m_x, left.m_y + right.m_y);
    // }


    //Implemantations
    double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

    Point operator+(const Point& left, const Point& right){
            return Point(left.m_x + right.m_x , left.m_y + right.m_y );
    }
    
} // namespace op_overloading_2

