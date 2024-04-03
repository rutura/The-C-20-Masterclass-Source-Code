#include <fmt/format.h>


void print_sum(int a, int b)
{

  int sum = a + b;
  fmt::println("sizeof(a) : {}", sizeof(a));
  fmt::println("sizeof(b) : {}", sizeof(b));
  fmt::println("sizeof(int) : {}", sizeof(int));
  fmt::println("sizeof(double) : {}", sizeof(double));
  fmt::println("sum : {}", sum);
}


int main()
{

  double a{ 4.5 };
  double b{ 7.8 };

  print_sum(a, b);

  return 0;
}