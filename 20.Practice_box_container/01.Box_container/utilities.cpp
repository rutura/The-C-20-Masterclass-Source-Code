#include "utilities.h"

#include "box_container.h"
#include "box_container_it_2.h"
#include "box_container_it_3.h"
#include "box_container_it_4.h"
#include "box_container_it_5.h"

#include <iostream>
#include <fmt/format.h>


void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

//#1
void constructing_destructing_demo(){

	iteration_1::BoxContainer box1(15);
	box1.dummy_initialize();

	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "&box1 : " << &box1 << std::endl;

	iteration_1::BoxContainer box2(box1);
	std::cout << "box2 : " << box2 << std::endl;
	std::cout << "&box2 : " << &box2 << std::endl;
}

//#2
void adding_items_demo(){
	iteration_2::BoxContainer box1(5);
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
}

//#3
void removing_items_demo(){

	iteration_3::BoxContainer box1;
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

}

//#4
void other_operators_demo(){
	//Operator+=
	iteration_4::BoxContainer box1;
	box1.add(1);
	box1.add(2);
	box1.add(3);

	std::cout << "box1 : " << box1 << std::endl;

	iteration_4::BoxContainer box2;
	box2.add(10);
	box2.add(20);
	box2.add(30);

	std::cout << "box2 : " << box2 << std::endl;

	std::cout << std::endl;
	std::cout << "operator+= : " << std::endl;
	box2+= box1;
	std::cout << "box2 : " << box2 << std::endl;
	box2.add(50);
	std::cout << "box2 : " << box2 << std::endl;

	std::cout << "--------------------------" << std::endl;

//----------------------------------------------------

	//Operator+
	std::cout << std::endl;
	std::cout << "operator+ : " << std::endl;

	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "box2 : " << box2 << std::endl;

	iteration_4::BoxContainer box3;
	box3.add(81);
	box3.add(82);

	std::cout << "box3 : " << box3 << std::endl;

	std::cout << "box1 + box3 : " << (box1 + box3) << std::endl;

	std::cout << "--------------------------" << std::endl;

//----------------------------------------------------

	//Operator=
	std::cout << std::endl;
	std::cout << "operator= : " << std::endl;

	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "box2 : " << box2 << std::endl;
	std::cout << "box3 : " << box3 << std::endl;

	box3 = box2;

	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "box2 : " << box2 << std::endl;
	std::cout << "box3 : " << box3 << std::endl;
}


//#5
void storing_different_types_demo(){

	iteration_5::DoubleContainer double_box1;
	double_box1.add(11.2);
	double_box1.add(33.5);

	std::cout << "double_box1 : " << double_box1 << std::endl;

	iteration_5::IntContainer int_box1;
	int_box1.add(10);
	int_box1.add(20);

	std::cout << "int_box1 : " << int_box1 << std::endl;

	iteration_5::CharContainer char_box1;
	char_box1.add('H');
	char_box1.add('e');
	char_box1.add('l');
	char_box1.add('l');
	char_box1.add('o');

	std::cout << "char_box1 : " << char_box1 << std::endl;

    char_box1.remove_all('l');
	std::cout << "char_box1 : " << char_box1 << std::endl;
}