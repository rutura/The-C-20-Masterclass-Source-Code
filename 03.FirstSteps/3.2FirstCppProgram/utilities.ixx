module;
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void print_number(int number) {
    fmt::println("Number : {}", number); 
}

export int add_numbers(int first_param, int second_param)
{
  int result = first_param + second_param;
  return result;
}