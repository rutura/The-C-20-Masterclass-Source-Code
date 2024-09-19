#pragma once

#include <fmt/format.h>

namespace virt_func_default_arg {
//Base class
class Base
{
public:
  Base();
  ~Base();

  virtual double add(double a = 5, double b = 5) const
  {
    fmt::println("Base::add() called");
    return (a + b + 1);
  }
};

//Derived class
class Derived : public Base
{
public:
  Derived();
  ~Derived();

  virtual double add(double a = 10, double b = 10) const override
  {
    fmt::println("Derived::add() called");
    return (a + b + 2);
  }
};
}// namespace virt_func_default_arg