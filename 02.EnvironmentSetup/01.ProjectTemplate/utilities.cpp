#include "utilities.h"

//#include <iostream>
#include <fmt/format.h>

void print_msg(std::string_view msg) {
  fmt::println("{}",msg);
  //std::cout << msg << std::endl;
}