module;

#include <string_view>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import pure_virt_func_abstract_classes;
import abstract_class_interfaces;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void pure_virt_func_abstract_classes_demo(){

		// Shape * shape_ptr = new Shape; // Compiler error

	const pure_virt_func_abstract_classes::Shape *shape_rect =
					 new pure_virt_func_abstract_classes::Rectangle(10, 10, "rect1");
	double surface = shape_rect->surface();
	fmt::println("dynamic type of shape_rect : {}", typeid(*shape_rect).name());
	fmt::println("The surface of shape rect is : {}", surface);


	fmt::println("--------------");

	const pure_virt_func_abstract_classes::Shape *shape_circle = 
					new pure_virt_func_abstract_classes::Circle(10, "circle1");
	surface = shape_circle->surface();
	fmt::println("dynamic type of shape_circle : {}", typeid(*shape_circle).name());
	fmt::println("The surface of the circle is : {}", surface);

}

export void abstract_class_interfaces_demo(){

	abstract_class_interfaces::Point p1(10,20);
	std::cout << "p1 : " << p1 << "\n";
	//operator<<(std::cout,p1);

	//std::cout << "------------" << std::endl;
	std::unique_ptr<abstract_class_interfaces::Animal> animal0 =
			 std::make_unique<abstract_class_interfaces::Dog>("stripes","dog1");
	std::cout << *animal0 << std::endl;

	std::unique_ptr<abstract_class_interfaces::Animal> animal1 =
			 std::make_unique<abstract_class_interfaces::Bird>("white","bird1");
	std::cout << *animal1 << std::endl;


	std::cout << "--------------" << std::endl;
	//Can even put animals in an array and print them polymorphically.
	std::shared_ptr<abstract_class_interfaces::Animal> animals[] {
		std::make_shared<abstract_class_interfaces::Dog>("stripes","dog2"),
		std::make_shared<abstract_class_interfaces::Cat>("black stripes","cat2"),
		std::make_shared<abstract_class_interfaces::Crow>("black wings","crow2"),
		std::make_shared<abstract_class_interfaces::Pigeon>("white wings","pigeon2")
	};
	std::cout << std::endl;
	std::cout << "Printing out animals array : " << std::endl;
	for(const auto& a : animals){
		std::cout << *a << std::endl;
	}	
}