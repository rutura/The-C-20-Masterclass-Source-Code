#include "utilities.h"

#include <fmt/format.h>

void print_msg(std::string_view msg) {
  fmt::println("{}",msg);
}

void print_number(int number) {
  fmt::println("value: {}",number);
}


