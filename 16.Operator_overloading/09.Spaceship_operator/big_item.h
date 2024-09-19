#pragma once

#include <fmt/format.h>

struct Integer
{
  Integer() = default;
  Integer(int n) : m_wraped_int{ n } {}
  int get() const { return m_wraped_int; }

  bool operator==(const Integer &right) const { return (m_wraped_int == right.m_wraped_int); }
  bool operator<(const Integer &right) const { return (m_wraped_int < right.m_wraped_int); }

private:
  int m_wraped_int{};
};


class BigItem
{
public:
  BigItem() = default;
  BigItem(int n) : BigItem(n, n, n) {}
  BigItem(int a_param, int b_param, int c_param) : a(a_param), b(b_param), c(c_param) {}

  // Ordering : compiler generates >, < , >=, <= and also puts in the == operator
  //auto operator<=>(const BigItem & right_operand) const = default;
  std::strong_ordering operator<=>(const BigItem &right_operand) const = default;

private:
  int a{ 1 };
  int b{ 2 };
  int c{ 3 };
  Integer d;
};