#include <fmt/format.h>

size_t sum_up_to_zero(size_t value)
{
  if (value != 0) return value + sum_up_to_zero(value - 1);
  return 0;
}

int main()
{

  fmt::println("result : {}", sum_up_to_zero(10));

  return 0;
}