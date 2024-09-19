#pragma once

#include <fmt/format.h>

namespace partial_specialization {
// Primary template
template<typename T1, typename T2> class Adder
{
public:
  T1 add(T1 a, T2 b)
  {
    fmt::println("Generic template class");
    return a + b;
  }
};

// Partial specialization for when the first type is int
template<typename T2> class Adder<int, T2>
{
public:
  void add(int a, T2 b)
  {
    fmt::println("Partial specialization with int as the first type");
    return a + b;
  }
};


//Partial specialization for function templates is not supported in C++.
// Generic template function
template<typename T1, typename T2> T1 add(T1 a, T2 b)
{
  fmt::println("Generic template function");
  return a + b;
}

//  This will not compile
/*
template <typename T2>
T1 add(int a, T2 b) {
    fmt::println("Partial specialization with int as the first type");
    return a + b;
}
*/

}// namespace partial_specialization