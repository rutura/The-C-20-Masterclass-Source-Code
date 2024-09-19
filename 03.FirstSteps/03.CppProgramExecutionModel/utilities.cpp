#include "utilities.h"

#include <fmt/format.h>

int f_add(int a, int b) { return a + b; }
void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void print_number(int number) { fmt::println("number = {}", number); }