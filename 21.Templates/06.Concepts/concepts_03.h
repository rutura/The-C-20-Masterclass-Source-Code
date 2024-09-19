#pragma once

#include <concepts>


namespace concepts_03 {

template<typename T> concept TinyType = requires(T t)
{
  sizeof(T) <= 4;// Simple requirement : Only enforces syntax
  requires sizeof(T) <= 4;// Nested requirements
};


// Compound requirement
template<typename T> concept Addable = requires(T a, T b)
{
  // noexcept is optional
  {
    a + b
  } -> std::convertible_to<int>;// Compound requirement
  // Checks if a + b is valid syntax, doesn't throw expetions(optional) , and the result
  // is convertible to int(optional)
};


Addable auto add(Addable auto a, Addable auto b) { return a + b; }

}// namespace concepts_03