module;
#include <string_view>
//#include <fmt/format.h> //GCC 14.2 Seems to have problems with fmt. Use iostream with this compiler.
#include <iostream>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	//fmt::println("{}",msg);
  std::cout << msg << std::endl;
}

export void print_number(int number) {
    //fmt::println("Number : {}", number); 
    std::cout << "Number : " << number << std::endl;
}

export int add_numbers(int first_param, int second_param)
{
  int result = first_param + second_param;
  return result;
}