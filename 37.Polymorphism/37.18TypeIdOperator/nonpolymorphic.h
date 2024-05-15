#ifndef NON_POLYMORPHIC_H
#define NON_POLYMORPHIC_H

#include <fmt/format.h>

class StaticBase
{
  void do_something() { fmt::println("StaticBase::do_something() called"); }
};

class StaticDerived : public StaticBase
{
  void do_something() { fmt::println("StaticDerived::do_something() called"); }
};


#endif// NON_POLYMORPHIC_H
