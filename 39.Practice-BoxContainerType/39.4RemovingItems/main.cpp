#include <iostream>
#include "boxcontainer.h"

int main(){

	BoxContainer box1;
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

    return 0;
}