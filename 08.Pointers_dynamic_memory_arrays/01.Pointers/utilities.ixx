module;
#include <string_view>
#include <fmt/format.h>

export module utilities; 

import pointer_basics;
import pointers_and_const;
import pointers_and_arrays;
import pointer_arithmetic;


export void pointer_basics_demo(){
	pointer_basics::tinker_with_pointers();
}

export void pointer_and_const_demo(){
	pointers_and_const::const_pointer_and_pointer_to_const();
}

export void pointers_and_arrays_demo(){
	//pointers_and_arrays::tinker_with_pointers_and_arrays();
	pointers_and_arrays::swap_addresses();
}

export void pointer_arithmetic_demo(){
	//pointer_arithmetic::p_a_navigation();
	pointer_arithmetic::p_a_distance();
}