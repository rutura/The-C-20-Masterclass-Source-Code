#include <iostream>
#include <memory>
#include "boxcontainer.h"

void populate_box(BoxContainer& box, int modifier){
	for(size_t i{0} ; i < 20 ; ++i){
		box.add((i+1)*modifier);
	}
}



int main(){

    BoxContainer box1;
	populate_box(box1,2);

    std::cout << "box1 : " << box1 << std::endl;

    BoxContainer box2;

	box2 = std::move(box1);

	std::cout << "------" << std::endl;

	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "box2 : " << box2 << std::endl;


	std::cout << "------" << std::endl;

    std::unique_ptr<int> ptr_int = std::make_unique<int>(33);

	std::cout << "*ptr_int : " << *ptr_int << std::endl;

	//std::unique_ptr<int> ptr_int_copy = ptr_int; // Compiler error.
	                                                // unique_ptr's copy constructor
	                                                // is deleted -- it's a move-only
	                                                // type, so it can only be moved,
	                                                // e.g. std::move(ptr_int).
	std::unique_ptr<int> ptr_int_copy = std::move(ptr_int);


	if(ptr_int){
		std::cout << "*ptr_int : " << *ptr_int << std::endl;
	}else{
		std::cout << "ptr_int doesn't contain any valid data" << std::endl;
	}
	std::cout << "*ptr_int_copy : " << *ptr_int_copy << std::endl;


  
    return 0;
}