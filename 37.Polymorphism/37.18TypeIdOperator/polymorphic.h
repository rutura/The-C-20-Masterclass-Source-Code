#ifndef POLYMORPHIC_H
#define POLYMORPHIC_H

#include <fmt/format.h>

class DynamicBase
{
public:
  virtual void do_something() { fmt::println("DynamicBase::do_something() called"); }
  virtual ~DynamicBase() = default;
};

class DynamicDerived : public DynamicBase
{
public:
  virtual void do_something() override { fmt::println("DynamicDerived::do_something() called"); }
  virtual ~DynamicDerived() = default;
};


#endif// POLYMORPHIC_H
