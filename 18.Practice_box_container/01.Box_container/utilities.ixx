module;
#include <string_view>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import box_container_it_1;
import box_container_it_2;
import box_container_it_3;
import box_container_it_4;
import box_container_it_5;


//#1
export void constructing_destructing_demo(){

	using iteration_1::BoxContainer;

	BoxContainer box1(15);
	box1.dummy_initialize();
	std::cout << "box1 : " << box1 << std::endl;

	BoxContainer box2(box1);	// Copy constructor
	std::cout << "box2 : " << box2 << std::endl;

	BoxContainer box3;	
	box3 = box1;	// Copy assignment
	std::cout << "box3 : " << box3 << std::endl;

}

//#2
export void adding_items_demo(){
	using iteration_2::BoxContainer;

	BoxContainer box1(5);
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
export void removing_items_demo(){
	using iteration_3::BoxContainer;
	
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
	
}

//#4
export void other_operators_demo(){
	using iteration_4::BoxContainer;
	//Operator+=
	BoxContainer box1;
	box1.add(1);
	box1.add(2);
	box1.add(3);
	
	std::cout << "box1 : " << box1 << std::endl;
	
	BoxContainer box2;
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
	
	BoxContainer box3;
	box3.add(81);
	box3.add(82);
	
	std::cout << "box3 : " << box3 << std::endl;
	
	std::cout << "box1 + box3 : " << (box1 + box3) << std::endl;

	std::cout << "--------------------------" << std::endl;
	
}


//#5
export void storing_different_types_demo(){
	using iteration_5::BoxContainer;
	using iteration_5::Point;

	// BoxContainer for int
    BoxContainer<int> int_box;
    int_box.add(10);
    int_box.add(20);
    int_box.add(30);
    //std::cout << "int_box: " << int_box << "\n";
	std::cout << "int_box : " << int_box << std::endl;

    // BoxContainer for double
    BoxContainer<double> double_box;
    double_box.add(10.5);
    double_box.add(20.3);
    double_box.add(30.7);
    std::cout << "double_box: " << double_box << "\n";

    // BoxContainer for std::string
    BoxContainer<std::string> string_box;
    string_box.add("Hello");
    string_box.add("World");
    string_box.add("C++");
    std::cout << "string_box: " << string_box << "\n";

	// BoxContainer for Point
    BoxContainer<Point> point_box;
    point_box.add(Point{1, 2});
    point_box.add(Point{3, 4});
    point_box.add(Point{5, 6});
    std::cout << "point_box: " << point_box << "\n";

    // Combining two BoxContainers for Point
    BoxContainer<Point> another_point_box;
    another_point_box.add(Point{7, 8});
    another_point_box.add(Point{9, 10});

    point_box += another_point_box;
    std::cout << "point_box after += another_point_box: " << point_box << "\n";
}