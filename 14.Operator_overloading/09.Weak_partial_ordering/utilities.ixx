module;
#include <string>
#include <cmath>
#include <string_view>
#include <fmt/format.h>

export module utilities; 

import ordering_1;
import ordering_2;
import ordering_3;

export void ordering_1_demo(){
    ordering_1::weak_ordering_ex1();
}

export void ordering_2_demo(){
    ordering_2::weak_ordering_ex2();
}

export void ordering_3_demo(){
    ordering_3::partial_ordering_example();
}





