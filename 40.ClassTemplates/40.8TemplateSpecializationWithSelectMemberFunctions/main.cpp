#include <iostream>
#include "boxcontainer.h"


int main(){

	BoxContainer<int> int_box;
	int_box.add(10);	
	int_box.add(11);
	int_box.add(62);
	int_box.add(330);
	int_box.add(3);
	int_box.add(7);
	int_box.add(9);
	int_box.add(8);
	
	std::cout << "int_box : " << int_box << std::endl;
	std::cout << "int_box.max : " << int_box.get_max() << std::endl;

    std::cout << "-------------" << std::endl;

	BoxContainer<const char*> char_ptr_box;
	
	char_ptr_box.add("Apple");
	char_ptr_box.add("Kiwi");
	char_ptr_box.add("Banana");
    char_ptr_box.add("Zeus");
	std::cout << "char_ptr_box : " << char_ptr_box << std::endl;
	std::cout << "char_ptr_box : " << char_ptr_box.get_max() << std::endl;
    

    return 0;
}