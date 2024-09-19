#pragma once

#include<fmt/format.h>


namespace implicit_instantiations {

// Define a class template
template<typename T> class MyClass
{
public:
  // A function that has no error
  void safeFunction() { fmt::println("{}", "Safe function called"); }

  // A function that has an error
  void errorFunction()
  {
    // Intentional error: assuming T is a class with a member function 'nonExistentFunction'
    T instance;
    instance.nonExistentFunction();// This will cause an error if instantiated
  }
};

}// namespace implicit_instantiations