#pragma once

#include <fmt/format.h>
#include <cstring>

namespace full_specialization {

// Generic (primary) template
template<typename T> class Adder
{
public:
  T add(T a, T b)
  {
    fmt::println("Generic template class");
    return a + b;
  }
};

// Full specialization for int
template<> class Adder<int>
{
public:
  int add(int a, int b)
  {
    fmt::println("Specialized template class for int");
    return a + b;
  }
};

//Full specialization for const char*
template<> class Adder<const char *>
{
public:
  char *add(char *a, char *b)
  {
    fmt::println("Specialized template class for const char*");
    return std::strcat(a, b);
  }
};

//Function template specialization
// Primary template
template<typename T> T add(T a, T b)
{
  fmt::println("Generic template function");
  return a + b;
}

template<> inline char *add<char *>(char *a, char *b)
{
  fmt::println("Specialized template function for char*");
  return std::strcat(a, b);
}

}// namespace full_specialization