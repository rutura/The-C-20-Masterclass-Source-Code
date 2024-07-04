module;

#include <fmt/format.h>

export module outer;

export class Outer
{
public:
  Outer(int int_param, double double_param);
  Outer();
  ~Outer();

  void do_something()
  {
    Inner inner1(10.0);
    //        fmt::println( "Created inner object with value : {}" ,inner1.get_double() );
    // inner1.inner_var; // Outer doesn't have access to private parts of Inner
    // Has to go through setters and getters

    inner1.do_something_with_outer(this);
  }


private:
  int m_var1;
  double m_var2;
  inline static int static_int{ 45 };
  // public :
  class Inner
  {
  public:
    Inner(double double_param);

    double get_double() const
    {
      // Accessing private parts of Outer
      // fmt::println( "Inner accessing m_var1 : " << m_var1 );// Compiler error.
      fmt::println("static_int : {}", static_int);
      return inner_var;
    }

    void do_something_with_outer(Outer *outer)
    {
      fmt::println("This is inner accessing private parts of outer object, m_var1 : {}", outer->m_var1);
    }

  private:
    double inner_var;
  };
};

//Implementations
Outer::Outer(int int_param, double double_param) : m_var1(int_param), m_var2(double_param) {}

// default constructor . Delegates to two param constructor
Outer::Outer() : Outer(0, 0.0) {}

Outer::~Outer() {}

Outer::Inner::Inner(double double_param) : inner_var(double_param) {}