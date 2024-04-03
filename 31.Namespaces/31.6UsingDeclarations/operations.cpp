#include <fmt/format.h>

const double adjustment{ 0.7234 };

namespace Math {
double add(double a, double b)
{
  fmt::println("Math::add");
  return a + b;
}
double sub(double a, double b)
{
  fmt::println("Math::sub");
  return a - b;
}
double mult(double a, double b)
{
  fmt::println("Math::mult");
  return a * b;
}
double div(double a, double b)
{
  fmt::println("Math::div");
  return a / b;
}

}// namespace Math

namespace Math_Weighted {
double add(double a, double b)
{
  fmt::println("Math_Weighted::add");
  return a + b - adjustment;
}
double sub(double a, double b)
{
  fmt::println("Math_Weighted::sub");
  return a - b - adjustment;
}
double mult(double a, double b)
{
  fmt::println("Math_Weighted::mult");
  return a * b - adjustment;
}
double div(double a, double b)
{
  fmt::println("Math_Weighted::div");
  return a / b - adjustment;
}
}// namespace Math_Weighted