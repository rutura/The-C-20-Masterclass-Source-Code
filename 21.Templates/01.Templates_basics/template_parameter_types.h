#pragma once

namespace template_parameter_types {

//Type template parameters
template<typename T> class Point
{
private:
  T x;
  T y;

public:
  Point(T x, T y)
    : x(x), y(y) {}

  T get_x() const { return x; }

  T get_y() const { return y; }

  Point operator+(const Point &other) { return Point(x + other.x, y + other.y); }
};

template<typename T>// Returns the maximum
T maximum(T a, T b) { return a > b ? a : b; }

//Can do defaults
template<typename T = int> T add(T a, T b) { return a + b; }


//Non-type template parameters
template<int N> class Array
{
private:
  int m_array[N];

public:
  int get_size() const { return N; }
};

}//namespace template_parameter_types