#include <fmt/format.h>


int max(int a, int b)
{
  fmt::println("int overload called");
  return (a > b) ? a : b;
}

double max(double a, double b)
{
  fmt::println("double overload called");
  return (a > b) ? a : b;
}

double max(int a, double b)
{
  fmt::println("(int,double) overload called");
  return (a > b) ? a : b;
}

double max(double a, int b)
{
  fmt::println("(double,int) overload called");
  return (a > b) ? a : b;
}

double max(double a, int b, int c)
{
  fmt::println("(double,int,int) overload called");
  return a;
}

std::string_view max(std::string_view a, std::string_view b)
{
  fmt::println("(string_view,string_view) overload called");
  return (a > b) ? a : b;
}

int main()
{

  int x{ 4 };
  int y{ 9 };
  double a{ 5.4 };
  double b{ 7.4 };

  auto result = max(b, x, y);

  max("Hello", "World");

  return 0;
}