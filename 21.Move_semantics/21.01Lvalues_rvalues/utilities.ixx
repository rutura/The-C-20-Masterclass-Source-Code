module;

#include <string_view>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import move_semantics_01;
import move_semantics_02;
import move_semantics_03;
import boxcontainer;
import move_semantics_04;
import move_semantics_05;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void move_semantics_01_demo(){
	move_semantics_01::try_out_move_semantics();
}

export void move_semantics_02_demo(){
	move_semantics_02::try_out_move_semantics();
}

export void move_semantics_03_demo(){

	box::BoxContainer<int> box_array[2];
    std::cout << "--------" << std::endl;

	for(size_t i{0} ; i < 2 ; ++i){
		box_array[i] = move_semantics_03::make_box(i+1);//Copy assignment operator called at each iteration
									// We're copying data from the temporary and 
									// throwing the temporary away (with data)
	}
    std::cout << "--------" << std::endl;
}

export void move_semantics_04_demo(){

	box::BoxContainer<int> box_array[2];
    std::cout << "--------" << std::endl;

	for(size_t i{0} ; i < 2 ; ++i){
		box_array[i] = move_semantics_04::make_box(i+1);//Move assignment operator called
	}
    std::cout << "--------" << std::endl;
}

export void move_semantics_05_demo(){
	box::BoxContainer<int> box1;
	move_semantics_05::populate_box(box1,2);
	box::BoxContainer<int> box2;
	move_semantics_05::populate_box(box2,15);
	
	std::cout << "box1 : " << box1 << "\n";
	std::cout << "box2 : " << box2 << "\n";
	
	move_semantics_05::swap_data(box1,box2);

  	std::cout << "-----" << "\n";

	std::cout << "box1 : " << box1 << "\n";
	std::cout << "box2 : " << box2 << "\n";
}