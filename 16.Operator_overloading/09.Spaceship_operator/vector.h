#pragma once

#include <compare>
#include <cmath>
#include <fmt/format.h>

class Vector{
    friend std::ostream &operator<<(std::ostream &out, const Vector &p);

    public:
    Vector() = default;
    Vector(double x, double y) : m_x{ x }, m_y{ y } {}

    Vector(double x_y) : Vector{ x_y, x_y } {}
    // Operators
    bool operator==(const Vector&other) const;
    std::partial_ordering operator<=>(const Vector&right) const;
    double x() const { return m_x; }
    double y() const { return m_y; }
    double length() const;// Function to calculate distance from the Vector(0,0)
    private:
    double m_x{};
  double m_y{};

};