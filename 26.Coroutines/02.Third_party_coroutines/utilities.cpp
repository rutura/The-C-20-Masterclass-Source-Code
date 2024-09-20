#include "utilities.h"
#include "practical_coro_01.h"

#include <fmt/format.h>
#include <iostream>

void print_msg(std::string_view msg) {
  fmt::println("{}",msg);
}

void practical_coro_01_demo(){
  for (auto i : practical_coro_01::fibonacci())
  {
    if (i > 1'000'000) break;
    std::cout << i << std::endl;
  }
}

void practical_coro_02_demo(){
  /*
      int max_value = 100;
  for (int value : fibonacci(max_value)) {
      std::cout << value << " ";
  }
  std::cout << std::endl;
      */
}