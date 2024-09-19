#include "scores.h"

#include <cassert>
#include <fmt/format.h>

Scores::Scores(const std::string &course_name): m_course_name{ course_name } {}

//Implementations
double &Scores::operator[](size_t index)
{
  assert((index >= 0) && (index < 20));
  return m_scores[index];
}

double Scores::operator[](size_t index) const
{
  assert((index >= 0) && (index < 20));
  return m_scores[index];
}

void Scores::print_info() const   {
  fmt::print("{} : [", m_course_name);
  for (size_t i{}; i < 20; ++i) { fmt::print("{}  ", m_scores[i]); }
  fmt::println("]");
}

