module;

#include <string_view>
#include <vector>
#include <fmt/format.h>

export module utilities; 

import iterator_adaptors_01;
import iterator_adaptors_03;

export void iterator_adaptors_01_demo(){
	iterator_adaptors_01::back_insert_iterator_test();
	fmt::println("====================================");
	iterator_adaptors_01::front_insert_iterator_test();
	fmt::println("====================================");
	iterator_adaptors_01::insert_iterator_test();
	fmt::println("====================================");
	iterator_adaptors_01::reverse_iterator_test();
}

export void iterator_adaptors_03_demo(){
	//iterator_adaptors_03::read_and_print();
	iterator_adaptors_03::read_sum_print();
}