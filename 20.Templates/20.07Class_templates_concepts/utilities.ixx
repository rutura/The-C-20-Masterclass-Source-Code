module;

#include <string_view>
#include <vector>
#include <iostream>
#include <concepts>
#include <fmt/format.h>

export module utilities; 

import boxcontainer;
import class_templates_concepts_01;
import class_templates_concepts_02;
import class_templates_concepts_03;
import class_templates_concepts_04;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void class_templates_concepts_01_demo(){

	class_templates_concepts_01::Point<int> point_int(10,20);
	std::cout << "point_int : " << point_int << std::endl;
	
	class_templates_concepts_01::Point<double> point_double(11.1,12.2);
	std::cout << "point_double : " << point_double << std::endl;

    
	//class_templates_concepts_01::Point<std::string> point_string("Hello","World");
    //std::cout << "point_string : " << point_string << std::endl;



	box::BoxContainer<class_templates_concepts_01::Point<int>> point_box;
	point_box.add(point_int);
	point_box.add(class_templates_concepts_01::Point<int>(40,50));
	
	std::cout << "point_box : " << point_box << std::endl;
}

export void class_templates_concepts_02_demo(){
	//Numbers
	//std::floating_point<T>
	/*
	static_assert(std::floating_point<int>);//Fails
	static_assert(std::floating_point<double>);
	*/

	//equality and order
	//https://en.cppreference.com/w/cpp/concepts/equality_comparable
	//static_assert(std::equality_comparable<int>); // == , !=
	//static_assert(std::equality_comparable_with<double,std::string>);

	//static_assert(std::totally_ordered<int>);
	//static_assert(std::totally_ordered<Point<int>>); // Needs all comparison operators



	//Others
	//std::same_as
	//static_assert(std::same_as<int,int>); // Success
	//static_assert(std::same_as<int,double>);// Fail
	//static_assert(std::same_as<class_templates_concepts_02::Dog,class_templates_concepts_02::Cat>); //Fail
	//static_assert(std::same_as<box::BoxContainer<int>, box::BoxContainer<int>>); // Success
	//static_assert(std::same_as<BoxContainer<int>, BoxContainer<double>>); // Fail
	static_assert(std::same_as<class_templates_concepts_02::Point<int>,class_templates_concepts_02::Point<int>>); // Success
	//static_assert(std::same_as<class_templates_concepts_02::Point<int>,class_templates_concepts_02::Point<float>>); // Fail
	

	//std::destructible
	//static_assert(std::destructible<Dog>);
	//std::derived_from : See official example  : https://en.cppreference.com/w/cpp/concepts/derived_from

	//std::copyable : needs a copy constructor
	//And much more
}

export void class_templates_concepts_03_demo(){

	//Set up a box container of int
	box::BoxContainer<int> int_box;
	int_box.add(10);
	int_box.add(20);
	int_box.add(30);
	//Print the box
	std::cout << "int_box : " << int_box << std::endl;

	box::BoxContainer<class_templates_concepts_03::Point> point_box;
	point_box.add({10,20});
	point_box.add({40,50});
	//Print the box
	std::cout << "point_box : " << point_box << std::endl;

}

export void class_templates_04_demo(){
	//static_assert(class_templates_concepts_04::Number<int>);
    auto result = class_templates_concepts_04::add(20.1, 20);
    std::cout << "result:  " << result << std::endl;
}