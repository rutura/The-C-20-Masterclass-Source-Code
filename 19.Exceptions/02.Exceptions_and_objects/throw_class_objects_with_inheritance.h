#pragma once

#include <string>
#include <fmt/format.h>


namespace throw_class_objects_with_inheritance {

class SomethingIsWrong
{
public:
  SomethingIsWrong(const std::string &s)
    : m_message(s) {}

  ~SomethingIsWrong() {}
  std::string what() const { return m_message; }

protected:
  std::string m_message;
};

class Warning : public SomethingIsWrong
{
public:
  Warning(const std::string &s)
    : SomethingIsWrong(s) {}

  std::string what() const { return m_message + " Yellow"; }
};

class SmallError : public Warning
{
public:
  SmallError(const std::string &s)
    : Warning(s) {}

  std::string what() const { return m_message + " Orange"; }
};

class CriticalError : public SmallError
{
public:
  CriticalError(const std::string &s)
    : SmallError(s) {}

  std::string what() const { return m_message + " Red"; }
};


//The do_something function
void do_something(size_t i);

}// namespace throw_class_objects_with_inheritance