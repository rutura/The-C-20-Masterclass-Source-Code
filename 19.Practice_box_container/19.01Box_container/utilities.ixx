module;
#include <string_view>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import box_container;
import box_container_it_2;
import box_container_it_3;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

//#1
export void constructing_destructing_demo(){

	iteration_1::BoxContainer box1(15);
	box1.dummy_initialize();
	
	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "&box1 : " << &box1 << std::endl;
	
	iteration_1::BoxContainer box2(box1);
	std::cout << "box2 : " << box2 << std::endl;
	std::cout << "&box2 : " << &box2 << std::endl;	
}

//#2
export void adding_items_demo(){
	iteration_2::BoxContainer box1(5);
	std::cout << "box1 : " << box1 << std::endl;

	box1.add(11);
	box1.add(12);
	box1.add(13);
	std::cout << "box1 : " << box1 << std::endl;
		
	box1.add(14);
	box1.add(15);
	std::cout << "box1 : " << box1 << std::endl;
		
	box1.add(16);
	std::cout << "box1 : " << box1 << std::endl;
		
	for(size_t i{0}; i < 4 ; ++i){
		box1.add(17+i);
	}
	std::cout << "box1 : " << box1 << std::endl;
	
	box1.add(21);
	std::cout << "box1 : "  << box1 << std::endl;
}

//#3
export void removing_items_demo(){
	
	iteration_3::BoxContainer box1;
	std::cout << "box1 : " << box1 << std::endl;
	
	box1.add(11);
	box1.add(12);
	box1.add(13);
	std::cout << "box1 : " << box1 << std::endl;
	
	box1.add(14);
	box1.add(15);
	std::cout << "box1 : " << box1 << std::endl;
	
	box1.add(16);
	std::cout << "box1 : " << box1 << std::endl;
	
	for(size_t i{0}; i < 4 ; ++i){
		box1.add(17+i);
	}
	std::cout << "box1 : " << box1 << std::endl;
	
	box1.add(21);
	std::cout << "box1 : "  << box1 << std::endl;
	
	std::cout << "---------------------------" << std::endl;

	std::cout << std::endl;
	std::cout << "Removing items : " << std::endl;
	
	box1.remove_item(15);
	std::cout << "box1 : " << box1 << std::endl;
	
	box1.remove_item(30);
	std::cout << "box1 : " << box1 << std::endl;
	
	box1.remove_item(18);
	std::cout << "box1 : " << box1 << std::endl;
	
	std::cout << "---------------------------" << std::endl;

	std::cout << std::endl;
	std::cout << "Removing all instances of an item" << std::endl;
	
	std::cout << "box1 : " << box1 << std::endl;
	
	box1.add(11);
	box1.add(33);
	box1.add(52);
	box1.add(11);

	std::cout << "box1 : " << box1 << std::endl;

	std::cout << "---------------------------" << std::endl;

	//Removing all instances  of 11
	std::cout << "Removing all instances of 11 : " << std::endl;
	box1.remove_all(11);
	std::cout << "box1 : " << box1 << std::endl;
	
}