#pragma once
#include <concepts>


namespace concepts_01 {
// Syntax1
/*
 template <typename T>
requires std::integral<T>
T add( T a, T b){
    return a + b;
}
*/

// Syntax2
/*
 template <std::integral T>
T add( T a, T b){
    return a + b;
}
*/

// Syntax3
/*
 auto add(std::integral auto a , std::integral auto b){
    return a + b;
}
*/

// Syntax4
template<typename T> T add(T a, T b) requires std::integral<T> { return a + b; }

template<typename T> T add(T a, T b) { return a + b; }

}// namespace concepts_01