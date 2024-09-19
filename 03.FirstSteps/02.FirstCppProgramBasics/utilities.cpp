#include "utilities.h"

//#include <fmt/format.h>
#include <iostream>

void print_msg(std::string_view msg)
{
  //fmt::println("{}",msg);
  std::cout << msg << std::endl;
}

void print_number(int number)
{
  //fmt::println("Number : {}", number);
  std::cout << "Number : " << number << std::endl;
}

int add_numbers(int first_param, int second_param)
{
  int result = first_param + second_param;
  return result;
}