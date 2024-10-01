module;

#include <cmath>
#include <fmt/format.h>
#include <cassert>

export module op_overloading_4;

namespace op_overloading_4{
    //#4: Overload the subscript operator for reading and writting
    export class Point
    {
    public:
    Point(double x, double y) : m_x(x), m_y(y) {}

    double &operator[](size_t index)
    {
        assert((index == 0) || (index == 1));
        return (index == 0) ? m_x : m_y;
    }

    void print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

    private:
    double length() const;// Function to calculate distance from the point(0,0)

    private:
    double m_x{};// 0
    double m_y{};// 1
    };

    //Implementations
    double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
        
} // namespace op_overloading_4