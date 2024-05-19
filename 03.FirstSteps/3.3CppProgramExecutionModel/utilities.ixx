module;
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview

export int f_add(int a, int b) {
    return a + b; 
}
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void print_number(int number){
  fmt::println("number = {}", number);
}