#pragma once
#include <compare>
#include <cmath>

//#1: Weak ordering example1
/*
class ComparableString
{
public:
  ComparableString(const std::string &str) : m_str{ str } {}

  std::weak_ordering operator<=>(const ComparableString &right_side) const
  {

    if (m_str.size() == right_side.m_str.size()) {
      return std::weak_ordering::equivalent;
    } else if (m_str.size() > right_side.m_str.size()) {
      return std::weak_ordering::greater;
    } else {
      return std::weak_ordering::less;
    }
  }

  bool operator==(const ComparableString &right_side) const { return (m_str.size() == right_side.m_str.size()); }

private:
  std::string m_str;
};
void weak_ordering_ex1();
std::weak_ordering case_insensitive_compare(const char *str1, const char *str2);
class CaseInsensitiveString
{
public:
  CaseInsensitiveString(const std::string &str) : s(str) {}
  std::weak_ordering operator<=>(const CaseInsensitiveString &b) const
  {
    return case_insensitive_compare(s.c_str(), b.s.c_str());
  }
  std::weak_ordering operator<=>(const char *b) const { return case_insensitive_compare(s.c_str(), b); }

  bool operator==(const CaseInsensitiveString &right_operand) const
  {
    return (case_insensitive_compare(s.c_str(), right_operand.s.c_str()) == std::weak_ordering::equivalent) ? true : false;
  }

private:
  std::string s;
};

void weak_ordering_ex2();
 */

class Point
{
public:
  Point(int x, int y) : m_x{ x }, m_y{ y } {}
  bool operator==(const Point &right) const { return length() == right.length(); }
  std::partial_ordering operator<=>(const Point &right) const
  {
    if (is_within_bounds(*this) && is_within_bounds(right)) {
      if (length() > right.length())
        return std::partial_ordering::greater;
      else if (length() < right.length())
        return std::partial_ordering::less;
      else
        return std::partial_ordering::equivalent;
    }
    return std::partial_ordering::unordered;
  }

private:
  bool is_within_bounds(const Point &p) const
  {
    if ((std::abs(p.m_x) < 100) && (std::abs(p.m_y) < 100)) return true;
    return false;
  }
  double length() const { return sqrt(pow(m_x - 0, 2) + pow(m_y - 0, 2) * 1.0); }
  int m_x{};
  int m_y{};
};

void partial_ordering_example();