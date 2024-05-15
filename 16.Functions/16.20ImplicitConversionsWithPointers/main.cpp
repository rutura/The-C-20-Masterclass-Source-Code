#include <fmt/format.h>

void print_sum(int *param1, int *param2) { fmt::println("sum : {}", (*param1 + *param2)); }

int main()
{

  int a{ 3 };
  int b{ 12 };

  print_sum(&a, &b);

  return 0;
}