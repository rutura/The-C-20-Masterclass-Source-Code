#pragma once


#include <fmt/format.h>


namespace typeid_operator {

//Polymorphic
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


//Non polymorphic
class StaticBase
{
  void do_something() { fmt::println("StaticBase::do_something() called"); }
};

class StaticDerived : public StaticBase
{
  void do_something() { fmt::println("StaticDerived::do_something() called"); }
};

}// namespace typeid_operator