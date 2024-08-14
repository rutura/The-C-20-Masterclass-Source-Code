module;

#include <string_view>
#include <vector>
#include <algorithm>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import custom_iterators_01;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


//Input iterators: read only
export void custom_iterators_01_demo(){

	//std::vector<int> box1 {8,1,4,2,5,3,7,9};
    custom_iterators_01::BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);
   
    //find algorithm
    if (std::ranges::find(box1, 8) != box1.end()) {
		fmt::println("numbers contains: {}",8);
    } else {
		fmt::println("numbers does not contain: {}",8);
    }

    //Won't work. Needs a bidirectional iterator
    //std::ranges::reverse(box1.begin(),box1.end());


    //Range based for loop
    for(auto n : box1){
		fmt::print("{} ",n);
    }
	  fmt::println("\n");

    custom_iterators_01::read_lines_from_file();

}

//Ouput iterators: write only - we go through operator* and operator-> to modify the value referenced by the iterator.
export void custom_iterators_02_demo(){

    custom_iterators_01::BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);
   
    std::cout << "box : " << box1 << std::endl;

    //Destination box
    custom_iterators_01::BoxContainer<int> box2;
    for(size_t i{}; i < box1.size();++i){
        box2.add(0);
    }
 
    std::cout << "box2-1 : " << box2 << std::endl;
	//The copy algorithm needs an output iterator to paste into the destination.
    std::ranges::copy(box1,box2.begin());
    std::cout << "box2-2 : " << box2 << std::endl;


}