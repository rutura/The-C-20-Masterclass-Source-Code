module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import containers_iterators_algorithms_01;
import containers_iterators_algorithms_02;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void containers_iterators_algorithms_01_demo(){
	containers_iterators_algorithms_01::use_vector();
	containers_iterators_algorithms_01::use_list();
	containers_iterators_algorithms_01::use_deque();
}

export void containers_iterators_algorithms_02_demo(){
	containers_iterators_algorithms_02::use_set();
	/*
	containers_iterators_algorithms_02::use_map();
	containers_iterators_algorithms_02::use_multiset();
	containers_iterators_algorithms_02::use_multimap();
	*/
}