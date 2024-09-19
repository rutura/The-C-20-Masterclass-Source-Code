#pragma once

#include <fmt/format.h>

namespace throw_class_objects {

class SomethingIsWrong
{
public:
  SomethingIsWrong(const std::string &s)
    : m_message(s) {}

  // Copy Constructor
  SomethingIsWrong(const SomethingIsWrong &source)
  {
    fmt::println("Copy constructor for SomethingIsWrong called");
    m_message = source.m_message;
  }

  // Destructor
  ~SomethingIsWrong() { fmt::println("SomethingIsWrong destructor called"); }
  const std::string &what() const { return m_message; }

private:
  std::string m_message;
};

void do_something(size_t i);

}// namespace throw_class_objects