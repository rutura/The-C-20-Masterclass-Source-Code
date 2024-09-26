module;

#include <string_view>
#include <memory>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import move_semantics_01;
import move_semantics_02;
import move_semantics_03;
import canvas; // This also imports pixel

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
	//move_semantics_03::canvas_move_semantics_demo_1();
	move_semantics_03::canvas_move_semantics_demo_2();
}