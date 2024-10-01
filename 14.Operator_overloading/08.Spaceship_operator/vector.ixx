module;

#include <compare>
#include <cmath>
#include <fmt/format.h>

export module vector;

export class Vector{
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

inline std::ostream &operator<<(std::ostream &out, const Vector&p)
{
  out << "Vector [ x : " << p.m_x << ", y : " << p.m_y << " length : " << p.length() << "]";
  return out;
}


double Vector::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }

bool Vector::operator==(const Vector &other) const { return (this->length() == other.length()); }

std::partial_ordering Vector::operator<=>(const Vector &right) const
{
  if (length() > right.length())
    return std::partial_ordering::greater;
  else if (length() == right.length())
    return std::partial_ordering::equivalent;
  else if (length() < right.length())
    return std::partial_ordering::less;
  else
    return std::partial_ordering::unordered;
}