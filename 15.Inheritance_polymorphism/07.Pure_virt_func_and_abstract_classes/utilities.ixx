module;

#include <string_view>
#include <iostream>
#include <fmt/format.h>

export module utilities; 

import inh_poly_1;
import inh_poly_2;

export void inh_poly_1_demo(){

	using inh_poly_1::Shape;
	using inh_poly_1::Rectangle;
	using inh_poly_1::Circle;

	//Shape * shape_ptr = new Shape; // Compiler error

	const Shape *shape_rect = new Rectangle(10, 10, "rect1");
	double surface = shape_rect->surface();
	fmt::println("dynamic type of shape_rect : {}", typeid(*shape_rect).name());
	fmt::println("The surface of shape rect is : {}", surface);

	const Shape *shape_circle = 
					new Circle(10, "circle1");
	surface = shape_circle->surface();
	fmt::println("dynamic type of shape_circle : {}", typeid(*shape_circle).name());
	fmt::println("The surface of the circle is : {}", surface);

}

export void inh_poly_2_demo(){
	using inh_poly_2::Animal;
	using inh_poly_2::Dog;
	using inh_poly_2::Cat;
	using inh_poly_2::Bird;
	using inh_poly_2::Crow;
	using inh_poly_2::Pigeon;
	using inh_poly_2::Point;


	Point p1(10,20);
	std::cout << "p1 : " << p1 << "\n";
	//operator<<(std::cout,p1);

	//std::cout << "------------" << std::endl;
	std::unique_ptr<Animal> animal0 =
			 std::make_unique<Dog>("stripes","dog1");
	std::cout << *animal0 << std::endl;

	std::unique_ptr<Animal> animal1 =
			 std::make_unique<Bird>("white","bird1");
	std::cout << *animal1 << std::endl;


	//Can even put animals in an array and print them polymorphically.
	std::shared_ptr<Animal> animals[] {
		std::make_shared<Dog>("stripes","dog2"),
		std::make_shared<Cat>("black stripes","cat2"),
		std::make_shared<Crow>("black wings","crow2"),
		std::make_shared<Pigeon>("white wings","pigeon2")
	};
	std::cout << std::endl;
	std::cout << "Printing out animals array : " << std::endl;
	for(const auto& a : animals){
		std::cout << *a << std::endl;
	}	
}