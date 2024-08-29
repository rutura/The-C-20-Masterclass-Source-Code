module;

#include <string_view>
#include <vector>
#include <fmt/format.h>

export module utilities; 

import iterator_adaptors_01;
import iterator_adaptors_02;
import iterator_adaptors_03;


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
}

export void iterator_adaptors_02_demo(){

	std::vector<iterator_adaptors_02::Item> items;
	items.reserve(2); // Make sure it has enough space to hold the elements
	iterator_adaptors_02::Item item;
	fmt::println("====================================");
	items.push_back(item);
	items.push_back(item);
	fmt::println("====================================");

	//Copy the elements from items in a destination vector
	//std::vector<iterator_adaptors_02::Item> dest{items.begin(), items.end()};


	//Move the elements from items in a destination vector
	std::vector<iterator_adaptors_02::Item> dest{
				std::make_move_iterator(items.begin()), 
				std::make_move_iterator(items.end())
	};
}


export void iterator_adaptors_03_demo(){
	//iterator_adaptors_03::read_and_print();
	iterator_adaptors_03::read_sum_print();
}