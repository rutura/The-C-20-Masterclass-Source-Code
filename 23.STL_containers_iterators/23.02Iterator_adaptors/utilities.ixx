module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import iterator_adaptors_01;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void iterator_adaptors_01_demo(){
	iterator_adaptors_01::back_insert_iterator_test();
	fmt::println("====================================");
	iterator_adaptors_01::front_insert_iterator_test();
	fmt::println("====================================");
	iterator_adaptors_01::insert_iterator_test();
	fmt::println("====================================");
	iterator_adaptors_01::reverse_iterator_test();
	fmt::println("====================================");
	iterator_adaptors_01::move_iterator_test();
}