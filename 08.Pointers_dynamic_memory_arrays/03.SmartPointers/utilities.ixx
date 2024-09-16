module;
#include <string_view>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import unique_pointers;
import shared_pointers;


export void unique_pointers_demo(){
	unique_pointers::tinker_with_unique_pointers();
}

export void shared_pointers_demo(){
	shared_pointers::tinker_with_shared_pointers();
}














