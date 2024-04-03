/*
    .Exploring weird integral types
*/
#include <fmt/format.h>

int main()
{

  short int var1{ 10 };// 2 bytes
  short int var2{ 20 };

  char var3{ 40 };// 1
  char var4{ 50 };

  fmt::print("size of var1 : {}\n", sizeof(var1));
  fmt::print("size of var2 : {}\n", sizeof(var2));
  fmt::print("size of var3 : {}\n", sizeof(var3));
  fmt::print("size of var4 : {}\n", sizeof(var4));

  auto result1 = var1 + var2;
  auto result2 = var3 + var4;

  fmt::print("size of result1 : {}\n", sizeof(result1));// 4
  fmt::print("size of result2 : {}\n", sizeof(result2));// 4
  return 0;
}