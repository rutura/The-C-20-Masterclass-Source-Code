#include "outer.h"


//Implementations
Outer::Outer(int int_param, double double_param) : m_var1(int_param), m_var2(double_param) {}

// default constructor . Delegates to two param constructor
Outer::Outer() : Outer(0, 0.0) {}

Outer::~Outer() {}

void Outer::do_something()
{
  Inner inner1(10.0);
  //        fmt::println( "Created inner object with value : {}" ,inner1.get_double() );
  // inner1.inner_var; // Outer doesn't have access to private parts of Inner
  // Has to go through setters and getters

  inner1.do_something_with_outer(this);
}

Outer::Inner::Inner(double double_param) : inner_var(double_param) {}

double Outer::Inner::get_double() const
{
  // Accessing private parts of Outer
  // fmt::println( "Inner accessing m_var1 : " << m_var1 );// Compiler error.
  fmt::println("static_int : {}", static_int);
  return inner_var;
}

void Outer::Inner::do_something_with_outer(Outer *outer)
{
  fmt::println("This is inner accessing private parts of outer object, m_var1 : {}", outer->m_var1);
}

