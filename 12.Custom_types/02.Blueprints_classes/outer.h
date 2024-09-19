#pragma once

#include <fmt/format.h>

class Outer
{
public:
  Outer(int int_param, double double_param);
  Outer();
  ~Outer();
  void do_something();

private:
  int m_var1;
  double m_var2;
  inline static int static_int{ 45 };
  // public :
  class Inner
  {
  public:
    explicit Inner(double double_param);

    [[nodiscard]] double get_double() const;

    void do_something_with_outer(Outer *outer);

  private:
    double inner_var;
  };
};
