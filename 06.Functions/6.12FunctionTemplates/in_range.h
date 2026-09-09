#pragma once

// A FUNCTION TEMPLATE is a pattern with the type left blank. `T` is a
// placeholder the compiler fills in from the arguments at each call,
// stamping out a concrete function on demand. One template stands in for
// a whole family of overloaded functions you would otherwise write by
// hand.
//
// WHY THE WHOLE THING LIVES IN THIS HEADER
// ---------------------------------------
// A template is not code yet - it is a recipe. The compiler can only
// turn `in_range<int>` into real code at a call site where it can SEE
// the template body. So the body must be visible in every .cpp that
// calls it, which in practice means: put it in a header and #include it.
//
// If you instead put the body in in_range.cpp, that .cpp has no calls,
// so it instantiates nothing and in_range.o is empty. Any other .cpp
// that calls in_range() compiles fine (it can see this declaration) but
// then the linker finds no in_range<int> anywhere:
//
//     undefined reference to `bool in_range<int>(int, int, int)`

template <typename T>
bool in_range(T value, T low, T high) {
    return low <= value && value <= high;
}
