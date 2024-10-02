/*
    . This file containes code that showcases the case where we need to set up
        a custom equality operator.
    . Here we need to compare Point objects based on their distance from the origin.
    . Once we set up the custom equality operator, the compiler will also generate
        the != operator.
    . It will not generate the logical operators like >, <, >=, <= though.
    . Here, default lexico graphical member wise comparison won't cut it for us.
*/
module;

#include <cmath>
#include <iostream>

export module spaceship_ops_3;

namespace spaceship_ops_3{

    export class Point
    {
    friend std::ostream &operator<<(std::ostream &out, const Point &p);

    public:
    Point() = default;
    Point(double x, double y) : m_x{ x }, m_y{ y } {}

    Point(double x_y) : Point{ x_y, x_y } {}
    // Operators
    bool operator==(const Point &other) const;
    double x() const { return m_x; }
    double y() const { return m_y; }
    double length() const;// Function to calculate distance from the point(0,0)
    private:
    double m_x{};
    double m_y{};
    };

    inline std::ostream &operator<<(std::ostream &out, const Point &p)
    {
        out << "Point [ x: " << p.m_x 
            << ", y : " << p.m_y 
            << " length: " << p.length() 
            << "]";
        return out;
    }

    //Implementations
    double Point::length() const {
        return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0);
    }

    bool Point::operator==(const Point &other) const {
        return (this->length() == other.length());
    }
} // namespace spaceship_ops_3