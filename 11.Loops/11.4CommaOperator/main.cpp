#include <fmt/format.h>

int main()
{

  // The comma operator combines
  // two or more  expressions into a single expression,
  //  where the value of the operation is the value of its right operand

  int increment{ 5 };
  int number1{ 10 };
  int number2{ 20 };
  int number3{ 25 };
  int result = (number1 *= ++increment, number2 - (++increment), number3 += ++increment);
  fmt::println("number1 : {}", number1);// 60
  fmt::println("number2 : {}", number2);// 20
  fmt::println("number3 : {}", number3);// 33
  fmt::println("result : {}", result);// 33

  return 0;
}