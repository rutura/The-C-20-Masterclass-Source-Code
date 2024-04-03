#include <fmt/format.h>

int global_var{ 44 };

int main()
{

  bool green{ false };

  global_var++;// 45

  if (green) {
    global_var++;
    int car_count{ 23 };
    fmt::println("Light is green {} on the move!", car_count);
  } else {
    // car_count++; // Compiler error
    global_var++;// 46
    fmt::println("Light is not green. Y'all should STOP!");
  }

  // car_count++;
  fmt::println("global_var : {}", global_var);

  return 0;
}