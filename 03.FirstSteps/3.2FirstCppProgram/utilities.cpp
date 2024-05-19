#include "utilities.h"

void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}
void print_number(int number) {
    fmt::println("Number : {}", number); 
}
int add_numbers(int first_param, int second_param)
{
  int result = first_param + second_param;
  return result;
}