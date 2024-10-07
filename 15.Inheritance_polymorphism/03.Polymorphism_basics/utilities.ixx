module;

#include <string_view>
#include <memory>
#include <vector>
#include <fmt/format.h>

export module utilities; 

import poly_1;
import poly_2;
import poly_3;
import poly_4;

//#1: Static binding demo
export void poly_1_demo(){

	// Creating instances of Shape, Oval, and Circle
    poly_1::Shape shape("Generic Shape");
    poly_1::Oval oval(5.0, 3.0, "Oval Shape");
    poly_1::Circle circle(7.0, "Circle Shape");

    // Managing objects via pointers
    poly_1::Shape* shape_ptr = &shape;
    poly_1::Shape* oval_ptr = &oval;    // Pointer to base class, but points to Oval object
    poly_1::Shape* circle_ptr = &circle; // Pointer to base class, but points to Circle object

    fmt::println("Calling draw() using Shape pointer (static binding):");
    shape_ptr->draw();   // Calls Shape's draw() (as expected)
    oval_ptr->draw();    // Still calls Shape's draw(), static binding
    circle_ptr->draw();  // Still calls Shape's draw(), static binding

    // Managing objects via references
    poly_1::Shape& shape_ref = shape;
    poly_1::Shape& oval_ref = oval;    // Reference to base class, refers to Oval object
    poly_1::Shape& circle_ref = circle; // Reference to base class, refers to Circle object

    fmt::println("\nCalling draw() using Shape reference (static binding):");
    shape_ref.draw();   // Calls Shape's draw() (as expected)
    oval_ref.draw();    // Still calls Shape's draw(), static binding
    circle_ref.draw();  // Still calls Shape's draw(), static binding

	//Calling the draw functions
	fmt::println("\nCalling the draw functions");
	poly_1::draw_shape(&circle);
	poly_1::draw_shape(circle);

}

export void poly_2_demo(){
	// Creating instances of Shape, Oval, and Circle
	poly_2::Shape shape("Generic Shape");
	poly_2::Oval oval(5.0, 3.0, "Oval Shape");
	poly_2::Circle circle(7.0, "Circle Shape");

	// Managing objects via pointers and references
	poly_2::Shape* shape_ptr = &shape;
	poly_2::Shape* oval_ptr = &oval;    // Pointer to base class, but points to Oval object
	poly_2::Shape* circle_ptr = &circle; // Pointer to base class, but points to Circle object

	fmt::println("Calling draw() using Shape pointer (polymorphism):");
	shape_ptr->draw();   // Calls Shape's draw() (as expected)
	oval_ptr->draw();    // Calls Oval's draw(), polymorphism
	circle_ptr->draw();  // Calls Circle's draw(), polymorphism

	// Managing objects via references
	poly_2::Shape& shape_ref = shape;
	poly_2::Shape& oval_ref = oval;    // Reference to base class, refers to Oval object
	poly_2::Shape& circle_ref = circle; // Reference to base class, refers to Circle object

	fmt::println("\nCalling draw() using Shape reference (polymorphism):");

	shape_ref.draw();   // Calls Shape's draw() (as expected)
	oval_ref.draw();    // Calls Oval's draw(), polymorphism
	circle_ref.draw();  // Calls Circle's draw(), polymorphism

	//Calling the draw functions
	fmt::println("\nCalling the draw functions");
	poly_2::draw_shape(&circle);
	poly_2::draw_shape(circle);

	//If dynamic memory is involved, use smart pointers.

	//Bring the classes into scope, to sharten the code.
	using poly_2::Shape;
    using poly_2::Oval;
    using poly_2::Circle;

	fmt::println("\nUsing smart pointers:");
    {
        std::unique_ptr<Shape> shape = std::make_unique<Shape>("Basic Shape");
        shape->draw(); // Calls Shape's draw()
    }  // shape goes out of scope and is destroyed here

    // Creating and using Oval
    {
        std::unique_ptr<Oval> oval = std::make_unique<Oval>(5.0, 10.0, "Oval Shape");
        oval->draw(); 	// Calls Oval's draw()
    }  // oval goes out of scope and is destroyed here

    // Creating and using Circle
    {
        std::unique_ptr<Circle> circle = std::make_unique<Circle>(7.0, "Circle Shape");
        circle->draw(); 		// Calls Circle's draw()
    }  // circle goes out of scope and is destroyed here

}

// #3: The need for virtual destructors
export void poly_3_demo(){

	//bad
	/*
	poly_3::bad::Base* obj = new poly_3::bad::Derived();
    obj->show();  // Calls Derived's show method due to virtual dispatch
    delete obj;   // Base class destructor is called, NOT Derived's!
	*/

	//good
	poly_3::good::Base* obj2 = new poly_3::good::Derived();
	obj2->show();  // Calls Derived's show method due to virtual dispatch
	delete obj2;   // Derived class destructor is called, as expected

}

// #4: Sizes and slicing
export void poly_4_demo(){

	//early binding
	fmt::println("\nObject sizes with static binding:");
	fmt::println("sizeof(Shape) : {}", sizeof(poly_4::early_binding::Shape));
	fmt::println("sizeof(Oval) : {}", sizeof(poly_4::early_binding::Oval));
	fmt::println("sizeof(Circle) : {}", sizeof(poly_4::early_binding::Circle));

	//late binding
	fmt::println("\nObject sizes with dynamic binding:");
	fmt::println("sizeof(Shape) : {}", sizeof(poly_4::late_binding::Shape));
	fmt::println("sizeof(Oval) : {}", sizeof(poly_4::late_binding::Oval));
	fmt::println("sizeof(Circle) : {}", sizeof(poly_4::late_binding::Circle));

	//Slicing 
	fmt::println("\nSlicing:");
	poly_4::late_binding::Circle circle1(3.3, "Circle1");
	poly_4::late_binding::Shape shape = circle1;
	shape.draw();// Shape::draw
}

// #4: Polymorphism and collections
export void polymorphism_and_collections_demo(){
	poly_2::Circle circle1(7.2, "circle1");
	poly_2::Oval oval1(13.3, 1.2, "Oval1");
	poly_2::Circle circle2(11.2, "circle2");
	poly_2::Oval oval2(31.3, 15.2, "Oval2");
	poly_2::Circle circle3(12.2, "circle3");
	poly_2::Oval oval3(53.3, 9.2, "Oval3");

	// The objects will be sliced as they are copied into the vector
	fmt::println("\nObject stored in vector of raw shapes: Slicing in action.");
	std::vector<poly_2::Shape> shapes1 {circle1, oval1, circle2, oval2, circle3, oval3};

	for (poly_2::Shape& s : shapes1) {
		s.draw(); //
	}

	// What if we store in references? Compiler error : references aren't left assignable
	// const poly_2::Shape& shapes2[] {circle1, oval1, circle2, oval2, circle3, oval3};

	// Raw pointers
	fmt::println("\nObject stored in vector of raw pointers: No slicing.");
	std::vector<poly_2::Shape*> shapes3 {&circle1, &oval1, &circle2, &oval2, &circle3, &oval3};

	for (poly_2::Shape* shape_ptr : shapes3) {
		shape_ptr->draw();
	}

	// Smart pointers
	fmt::println("\nObject stored in vector of smart pointers: No slicing.");
	std::vector<std::shared_ptr<poly_2::Shape>> shapes4 { 
		std::make_shared<poly_2::Circle>(12.2, "Circle4"),
		std::make_shared<poly_2::Oval>(10.0, 20.0, "Oval4") 
	};
	for (auto& s : shapes4) {
		s->draw(); 
	}

}