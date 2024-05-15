#include <fmt/format.h>

int main()
{
  double first_number{ 5.0 };
  double second_number{ 33.1 };
  char c{ '+' };

  switch (c) {
  case '+':
    fmt::println("{} + {} = {}", first_number, second_number, first_number + second_number);
    break;

  case '-':
    fmt::println("{} - {} = {}", first_number, second_number, first_number - second_number);
    break;

  case 'x':
    fmt::println("{} x {} = {}", first_number, second_number, first_number * second_number);

    break;

  case '/':
    fmt::println("{} / {} = {}", first_number, second_number, first_number / second_number);

    break;
  }
  return 0;
}
