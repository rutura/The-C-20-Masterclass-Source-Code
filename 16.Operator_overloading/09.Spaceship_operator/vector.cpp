#include "vector.h"


std::ostream &operator<<(std::ostream &out, const Vector&p)
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