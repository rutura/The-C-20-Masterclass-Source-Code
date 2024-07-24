module;
#include <string_view>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import box_container;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void constructing_destructing_demo(){

	iteration_1::BoxContainer box1(15);
	box1.dummy_initialize();
	
	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "&box1 : " << &box1 << std::endl;
	
	iteration_1::BoxContainer box2(box1);
	std::cout << "box2 : " << box2 << std::endl;
	std::cout << "&box2 : " << &box2 << std::endl;	
}