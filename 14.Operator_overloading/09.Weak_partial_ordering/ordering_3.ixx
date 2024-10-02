/*
    . This file contains code that showcases an example of partial ordering.
    . This kind of ordering is used when the type can have values you can't 
        compare to others.
    . For example, the Point below only models point that live within the [100,100] bounds.
    . If a point is outside of these bounds, it can't be compared to other points.
    . We can model that idea with partial ordering.
    . If a point isn't comparable to others, all attempts to compare
        it to other poitnts using the logical operators (==, !=, <, <=, >, >=) will return false.
        . see example.
*/
module;

#include <cmath>
#include <compare>
#include <fmt/format.h>

export module ordering_3;

namespace ordering_3{

    // Partial ordering example

    // Valid comparable points are within the [100,100] bounds
    class Point
    {
    public:
    Point(int x, int y) : m_x{ x }, m_y{ y } {}
    //bool operator==(const Point &right) const { return length() == right.length(); }
    bool operator==(const Point &right) const {
        return (*this <=> right) == std::partial_ordering::equivalent;
    }
    std::partial_ordering operator<=>(const Point &right) const
    {
        if (is_within_bounds(*this) && is_within_bounds(right)) {
        if (length() > right.length())
            return std::partial_ordering::greater;
        else if (length() < right.length())
            return std::partial_ordering::less;
        else
            return std::partial_ordering::equivalent;
        }
        return std::partial_ordering::unordered;
    }

    private:
    bool is_within_bounds(const Point &p) const
    {
        if ((std::abs(p.m_x) < 100) && (std::abs(p.m_y) < 100)) return true;
        return false;
    }
    double length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
    int m_x{};
    int m_y{};
    };

    export void partial_ordering_example(){

        Point p1(110, 110);
        Point p2(20, 20);

        auto result1 = (p1 > p2);
        fmt::println("p1 > p2 : {}", result1);

        auto result2 = (p1 >= p2);
        fmt::println("p1 >= p2 : {}", result2);

        auto result3 = (p1 == p2);
        fmt::println("p1 == p2 : {}", result3);

        auto result4 = (p1 != p2);
        fmt::println("p1 != p2 : {}", result4);

        auto result5 = (p1 < p2);
        fmt::println("p1 < p2 : {}", result5);

        auto result6 = (p1 <= p2);
        fmt::println("p1 <= p2 : {}", result6);
    }
    
} // namespace ordering_3