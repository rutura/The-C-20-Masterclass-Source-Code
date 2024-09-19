/*
    How It Works:

        . Base Case:
            . The base case function takes two parameters of type T and returns
   their sum. . This base case handles the situation where there are exactly two
   arguments left to process.

        . Variadic Template:
            . The variadic template function uses a template parameter pack
   (Args...) to accept an arbitrary number of arguments. . It adds the first
   argument (first) to the result of calling add recursively on the remaining
   arguments (args...). . The recursion eventually reduces the problem to the
   base case of adding two parameters.

        . This function template can handle any number of arguments and sum them
   up correctly.

*/
#pragma once

namespace variadic_function_templates {

// Base case to add two numbers
template<typename T> T add(T a, T b) { return a + b; }

template<typename T, typename... Args>// Args is a template parameter pack
T add(T first, Args... args)
{
  // Args... is a function parameter pack
  return (first + add(args...));// args is a parameter pack expansion.
  // return add(first, add(args...));
}


//Another implementation using the size of operator together with if constexpr
//The compiler still generates different overloads for each number of arguments.
template<typename T, typename... Args> T add2(T first, Args... args)
{
  if constexpr (sizeof...(args) == 0) { return first; } else { return first + add2(args...); }
}

}// namespace variadic_function_templates