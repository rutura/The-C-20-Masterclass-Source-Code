#pragma once

#include <string>
#include <fmt/format.h>

namespace ellipsis_catch_all {

class SomethingIsWrong
{
public:
  SomethingIsWrong(const std::string &s)
    : m_message(s) {}

  virtual ~SomethingIsWrong() {}
  virtual std::string what() const { return m_message; }

protected:
  std::string m_message;
};

class Warning : public SomethingIsWrong
{
public:
  Warning(const std::string &s)
    : SomethingIsWrong(s) {}

  virtual std::string what() const override { return m_message + " Yellow"; }
};

class SmallError : public Warning
{
public:
  SmallError(const std::string &s)
    : Warning(s) {}

  virtual std::string what() const override { return m_message + " Orange"; }
};

class CriticalError : public SmallError
{
public:
  CriticalError(const std::string &s)
    : SmallError(s) {}

  virtual std::string what() const override { return m_message + " Red"; }
};

void some_function(size_t i);

}// namespace ellipsis_catch_all