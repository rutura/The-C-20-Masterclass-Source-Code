#pragma once


#include <fmt/format.h>

namespace noexcept_specifier {

class Item
{
public:
  Item() {}

  void do_something_in_class() const noexcept
  {
    fmt::println("Doing something from class");
    try { throw 1; } catch (int ex) {
      fmt::println("Handling exception in Item::do_something_in_class");
      // throw; // Rethrowing in noexcept function/method will terminate program
    }
  }

private:
  int m_member_var;
};

void some_function() noexcept;

}// namespace noexcept_specifier