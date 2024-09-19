#pragma once

#include <fmt/format.h>


namespace lambdas_05 {

class Item
{
public:
  Item(int a, int b)
    : m_var1{ a }, m_var2{ b } {}

  void some_member_func()
  {
    auto func = [this]() { fmt::println("member vars : {} , {}", m_var1, m_var2); };
    func();
  };

private:
  int m_var1;
  int m_var2;
};

}// namespace lambdas_05