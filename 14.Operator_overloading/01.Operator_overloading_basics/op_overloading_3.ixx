module;

#include <cmath>
#include <fmt/format.h>
#include <cassert>

export module op_overloading_3;

namespace op_overloading_3{

    //#3: Overload the subscript operator for Point
    // It should be set up as a non-static member function. If you don't do this, you will get a compiler error.
    export class Point
    {
    public:
    Point() = default;
    Point(double x, double y) : m_x(x), m_y(y) {}
    ~Point() = default;

    double operator[](size_t index) const
    {
        assert((index == 0) || (index == 1));
        if (index == 0) {
        return m_x;
        } else {
        return m_y;
        }
    }

    void print_info() { fmt::println("Point [ x : {}, y: {}] ", m_x, m_y); }

    private:
    double length() const;// Function to calculate distance from the point(0,0)

    private:
    double m_x{};// 0
    double m_y{};// 1
    };

    //Implementation
    double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
        
} // namespace op_overloading_3