module;
#include <string_view>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import dynamic_allocation;


export void dynamic_memory_allocation_demo(){

	//dynamic_allocation::new_and_delete();
    //dynamic_allocation::dangling_pointers();
    //dynamic_allocation::when_new_fails();
    //dynamic_allocation::null_ptr_safety();
    //dynamic_allocation::memory_leaks();
    dynamic_allocation::dynamically_allocated_arrays();

}





