module;

#include <string_view>
#include <fmt/format.h>
#include <memory>
#include <vector>

export module utilities;

import poly_1;
import poly_2;
import poly_3;

//#1: Overloading, overriding and hiding
export void poly_1_demo(){

	//Add a few using declarations
	using poly_1::Shape;
	using poly_1::Oval;
	using poly_1::Circle;

	// Create a vector of unique_ptr to Shape
    std::vector<std::unique_ptr<Shape>> shapes;

    // Add shapes to the vector
    shapes.emplace_back(std::make_unique<Shape>("Generic Shape"));
    shapes.emplace_back(std::make_unique<Oval>(3.0, 5.0, "Oval Shape"));
    shapes.emplace_back(std::make_unique<Circle>(4.0, "Circle Shape"));

    // Drawing all shapes using polymorphism
    for (const auto& shape : shapes) {
        shape->draw();  // Calls the appropriate draw function (overridden)
    }

    // Demonstrating overloaded draw function
    shapes[1]->draw(24);  // Calls Oval's draw(int) (overloaded)

	//The cast below is necessary because the draw member with two members
	//is not part of the Shape's interface. We cast to Oval* because we know
	//that the second element in the vector is an Oval.
    static_cast<Oval*>(shapes[1].get())->draw(24, "Blue");  // Calls Oval's overloaded draw(int, std::string_view)

	//Set up a Oval object and call the draw() function
	//Oval oval(3.0, 5.0, "Oval Shape");
	//oval.draw();  // Calls Oval's draw() (overridden)
}

//#2: Polymorphism at different levels
export void poly_2_demo(){

	// Animal polymorphism
	poly_2::Dog dog1("dark gray", "dog1");
	poly_2::Cat cat1("black stripes", "cat1");
	poly_2::Pigeon pigeon1("white", "pigeon1");
	poly_2::Crow crow1("black", "crow1");

	poly_2::Animal *animals[]{ &dog1, &cat1, &pigeon1, &crow1 };
	fmt::println("\nAnimal polymorphism: ");
	for (const auto &animal : animals) { animal->breathe(); }


	// Feline polymorphism
	poly_2::Dog dog2("dark gray", "dog2");
	poly_2::Cat cat2("black stripes", "cat2");
	poly_2::Pigeon pigeon2("white", "pigeon2");// Putting pigeon in felines will result in compiler error
										//  pigeon is and Animal,a but is not a feline.
	poly_2::Animal animal1("some animal");

	poly_2::Feline *felines[]{ &dog2, &cat2 };
	fmt::println("\nFeline polymorphism: ");
	for (const auto &feline : felines) { feline->run(); }

	fmt::println("------------");

	// Bird polymorphism
	poly_2::Pigeon pigeon3("white", "pigeon1");
	poly_2::Crow crow3("black", "crow1");

	poly_2::Bird *birds[]{ &pigeon3, &crow3 };
	fmt::println("\nBird polymorphism: ");
	for (const auto &bird : birds) { bird->fly(); }
}

//#3: Static members in polymorphic classes
export void poly_3_demo() {
	// Shape
	poly_3::Shape shape1("shape1");
	fmt::println("shape count : {}", poly_3::Shape::get_static_count()); // 1

	poly_3::Shape shape2("shape2");
	fmt::println("shape count : {}", poly_3::Shape::get_static_count());// 2

	poly_3::Shape shape3;
	fmt::println("shape count : {}", poly_3::Shape::get_static_count());// 3

	fmt::println("***********************************************");

	// Ellipse
	poly_3::Ellipse ellipse1(10, 12, "ellipse1");
	fmt::println("shape count : {}", poly_3::Shape::get_static_count());// 4
	fmt::println("ellipse count : {}", poly_3::Ellipse::get_static_count());// 1


	fmt::println("***********************************************");

	// Shape polymorphism
	poly_3::Shape *shapes[]{ &shape1, &ellipse1 };
	for (auto &s : shapes) { fmt::println("count : {}", s->get_count());
	}

	fmt::println("\nA base class pointer to a Ellipse object: ");
	std::unique_ptr<poly_3::Shape> shapePtr = std::make_unique<poly_3::Ellipse>(5.0, 10.0, "My Ellipse");

    // This will call Ellipse's get_count, returning Ellipse's count
    fmt::println("Count from Shape pointer: {}", shapePtr->get_count());

    // Accessing static counts directly
    fmt::println("Shape count: {}", poly_3::Shape::get_static_count());
    fmt::println("Ellipse count: {}", poly_3::Ellipse::get_static_count());
} 