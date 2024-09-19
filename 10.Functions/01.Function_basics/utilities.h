#pragma once
#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg);

void print_number(auto number)
{
    fmt::println("{}", number);
}

void enter_bar(size_t age);
void say_hello();
double increment_multiply(double a, double b);
// Function that takes no parameters and return something
constexpr int lucky_number() { return 99; }
