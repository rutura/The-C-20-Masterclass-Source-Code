module;

#include <fmt/format.h>
#include <cmath>

export module point;

export class Point
{
  friend std::ostream &operator<<(std::ostream &out, const Point &p);
  friend bool operator>(const Point &left, const Point &right);
  friend bool operator>=(const Point &left, const Point &right);
  friend bool operator==(const Point &left, const Point &right);
  friend bool operator!=(const Point &left, const Point &right);
  friend bool operator<(const Point &left, const Point &right);
  friend bool operator<=(const Point &left, const Point &right);

public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}
  ~Point() = default;
  // Operators: can also do them as members.
  /*
  bool operator> (const Point& other) const;
  bool operator< (const Point& other) const;
  bool operator>=(const Point& other) const;
  bool operator<=(const Point& other) const;
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
  */
  double length() const;// Function to calculate distance from the point(0,0)
private:
  double m_x{};
  double m_y{};
};

inline std::ostream &operator<<(std::ostream &out, const Point &p)
{
  out << "Point [ x : " << p.m_x << ", y : " << p.m_y << " length : " << p.length() << "]";
  return out;
}

inline bool operator>(const Point &left, const Point &right) { return (left.length() > right.length()); }

inline bool operator>=(const Point &left, const Point &right) { return (left.length() >= right.length()); }

inline bool operator==(const Point &left, const Point &right) { return (left.length() == right.length()); }

inline bool operator!=(const Point &left, const Point &right) { return (left.length() != right.length()); }

inline bool operator<(const Point &left, const Point &right) { return (left.length() < right.length()); }

inline bool operator<=(const Point &left, const Point &right) { return (left.length() <= right.length()); }


//Implementations
double Point::length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }


/*
bool Point:: operator>(const Point& other)const{
    return (this->length() > other.length());
}

bool Point::operator< (const Point& other) const{
    return (this->length() < other.length());
}
bool Point::operator>=(const Point& other) const{
    return (this->length() >= other.length());
}
bool Point::operator<=(const Point& other) const{
    return (this->length() <= other.length());
}
bool Point::operator==(const Point& other) const{
    return (this->length() == other.length());
}
bool Point::operator!=(const Point& other) const{
    return (this->length() != other.length());
}
*/
