module;

#include <string_view>
#include <memory>
#include <fmt/format.h>

export module utilities; 

import static_binding;
import polymorphism;
import sizes_and_slicing;
import polymorphism_and_collections;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


void draw_circle(const static_binding::Circle &circle) { circle.draw(); }

void draw_oval(const static_binding::Oval &oval) { oval.draw(); }
// More functions as you deal with more shape types. 30 ? 70? 100? It's messy.

export void static_binding_demo(){

	static_binding::Shape shape1("Shape1");
	//shape1.draw();

	static_binding::Oval oval1(2.0, 3.5, "Oval1");
	//oval1.draw();

	static_binding::Circle circle1(3.3, "Circle1");
	//circle1.draw();

	// Base pointers
	/*
	static_binding::Shape *shape_ptr = &shape1;
	// shape_ptr->draw();

	static_binding::shape_ptr = &oval1;
	// shape_ptr->draw(); // Draw an oval

	shape_ptr = &circle1;
	// shape_ptr->draw();


	// Base references
	static_binding::Shape &shape_ref = circle1;
	// shape_ref.draw();


	// Drawing shapes
	draw_circle(circle1);
	draw_oval(oval1);


	// Shapes stored in collections
	static_binding::Circle circle_collection[]{ circle1, Circle(10.0, "Circle2"), Circle(20.0, "Circle3") };
	static_binding::Oval oval_collection[]{ oval1, Oval(22.3, 51.1, "Oval2") };
	// More arrays as you have more shape types, 100? Messy right?
	*/
}




void draw_shape(polymorphism::Shape *s) {
	s->draw(); 
}

void draw_shape_v1(const polymorphism::Shape &s_r) {
	s_r.draw(); 
}

export void polymorphism_demo(){

	polymorphism::Shape shape1("Shape1");
	shape1.draw();

	//polymorphism::Oval oval1(2.0, 3.5, "Oval1");
	// oval1.draw();

	//polymorphism::Circle circle1(3.3, "Circle1");
	// circle1.draw();


	// Base pointers
	/*
	polymorphism::Shape *shape_ptr = &shape1;
	// shape_ptr->draw(); // Shape::draw

	shape_ptr = &oval1;
	// shape_ptr->draw(); // Oval::draw()

	shape_ptr = &circle1;
	// shape_ptr->draw(); // Circle::draw()


	// Base references
	polymorphism::Shape &shape_ref = circle1;
	// shape_ref.draw(); // Cicle::draw()


	// Drawing shapes
	// draw_shape(&circle1);
	// draw_shape_v1(circle1);


	// Raw pointers
	shape_ptr = &oval1;
	// shape_ptr->get_x_rad();


	// Shapes stored in collections
	polymorphism::Shape *shape_collection[]{ &shape1, &oval1, &circle1 };

	for (polymorphism::Shape *s_ptr : shape_collection) { s_ptr->draw(); }
	*/
}

export void sizes_and_slicing_demo(){
	// Comparing object sizes
	fmt::println("sizeof(Shape) : {}", sizeof(sizes_and_slicing::Shape));// dynamic : 40
	fmt::println("sizeof(Oval) : {}", sizeof(sizes_and_slicing::Oval));// dynamic : 56
	fmt::println("sizeof(Circle) : {}", sizeof(sizes_and_slicing::Circle));// dynamic : 56


	// // Slicing
	sizes_and_slicing::Circle circle1(3.3, "Circle1");
	sizes_and_slicing::Shape shape = circle1;
	shape.draw();// Shape::draw
}

export void polymorphism_and_collections_demo(){

	polymorphism_and_collections::Circle circle1(7.2, "circle1");
	polymorphism_and_collections::Oval oval1(13.3, 1.2, "Oval1");
	polymorphism_and_collections::Circle circle2(11.2, "circle2");
	polymorphism_and_collections::Oval oval2(31.3, 15.2, "Oval2");
	polymorphism_and_collections::Circle circle3(12.2, "circle3");
	polymorphism_and_collections::Oval oval3(53.3, 9.2, "Oval3");


	// If you store raw object data in an array set up to store base class objects
	// the data is going to be sliced off!
	fmt::println( "sizeof (circle1) : {}" , sizeof(circle1) );
	polymorphism_and_collections::Shape shapes1[] {circle1,oval1,circle2,oval2,circle3,oval3};

	for(polymorphism_and_collections::Shape& s : shapes1){
		fmt::println( "sizeof (object) : {}" , sizeof(s) );
		s.draw(); //
	}

	// What if we store in references? Compiler error : references aren't left assignable
	// const polymorphism_and_collections::Shape& shapes2[] {circle1,oval1,circle2,oval2,circle3,oval3};


	// Raw pointers
	/*
	polymorphism_and_collections::Shape* shapes3[] {&circle1,&oval1,&circle2,&oval2,&circle3,&oval3};

	for ( polymorphism_and_collections::Shape* shape_ptr : shapes3){
		fmt::println( "Inside array , sizeof(*shape_ptr) : {}" , sizeof(*shape_ptr) );
		shape_ptr->draw();
	}
	*/


	// Smart pointers
	/*
	std::shared_ptr<polymorphism_and_collections::Shape> shapes4[]{ 
		std::make_shared<polymorphism_and_collections::Circle>(12.2, "Circle4"),
		std::make_shared<polymorphism_and_collections::Oval>(10.0, 20.0, "Oval4") 
	};
	for (auto &s : shapes4) {
		 s->draw(); 
	}
	*/

}