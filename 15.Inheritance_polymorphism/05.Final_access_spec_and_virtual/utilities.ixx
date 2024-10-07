module;
#include <string_view>
#include <fmt/format.h>
#include <memory>

export module utilities;

import inh_poly_1;
import inh_poly_2;
import inh_poly_3;
import inh_poly_4;

//#1: The final identifier
export void inh_poly_1_demo(){

	inh_poly_1::Animal animal{"Generic Animal"};
    animal.breathe();

    inh_poly_1::Dog dog{"Short fur", "Dog"};
    dog.run();  // Dog::run called
    dog.bark(); // Dog::bark called: Woof!

    inh_poly_1::BullDog bulldog;
    bulldog.run(); // Inherited Dog::run, no override allowed
    bulldog.bark(); // Inherited Dog::bark

    inh_poly_1::Cat cat{"Soft fur", "Cat"};
    cat.run();  // Cat::run called, overridden from Feline
    cat.miaw(); // Cat::miaw() called

    inh_poly_1::Bird bird{"White wings", "Bird"};
    bird.fly(); // Bird::fly() called

    inh_poly_1::Crow crow{"Black wings", "Crow"};
    crow.fly(); // Bird::fly() called, final prevents override
    crow.cow(); // Crow::cow() called

}

//#2: Final and override are not keywords
export void inh_poly_2_demo(){
	//No implementation here.
}

//#3: Polymorphic functions and access specifiers
export void inh_poly_3_demo(){

	//Dynamic binding
	{
		fmt::println("\nDynamic binding");
		using inh_poly_3::dyn_bind::Shape;
		using inh_poly_3::dyn_bind::Ellipse;

		// Accessing stuff through the base class pointer
		std::shared_ptr<Shape> shape0 = 
						std::make_shared<Ellipse>(1, 5, "ellipse0");
		shape0->draw();// Polymorphism
		// shape0->func(); // Error :  func is private in Shape

		// Direct objects : static binding
		Ellipse ellipse1(1, 6, "ellipse1");
		ellipse1.func();// Works
		//ellipse1.draw(); //Error : draw() is private in Ellipse.- Static binding

		// Raw derived object assigned to raw base object
		// Slicing will occur, Shape::draw will be called
		Shape shape3 = Ellipse(2, 3, "ellipse3");
		shape3.draw();// Shape::draw() called
		// shape3.func(); // Error : func is private in shape
	}

	//Static binding
	{
		fmt::println("\nStatic binding");
		using inh_poly_3::stat_bind::Shape;
		using inh_poly_3::stat_bind::Ellipse;

		// Accessing stuff through the base class pointer
		std::shared_ptr<Shape> shape0 = 
						std::make_shared<Ellipse>(1, 5, "ellipse0");
		shape0->draw();// Polymorphism
		// shape0->func(); // Error :  func is private in Shape

		// Direct objects : static binding
		Ellipse ellipse1(1, 6, "ellipse1");
		ellipse1.func();// Works
		//ellipse1.draw(); //Error : draw() is private in Ellipse.- Static binding

		// Raw derived object assigned to raw base object
		// Slicing will occur, Shape::draw will be called
		Shape shape3 = Ellipse(2, 3, "ellipse3");
		shape3.draw();// Shape::draw() called
		// shape3.func(); // Error : func is private in shape
	}
}


export void inh_poly_4_demo(){
		fmt::println("\nBase ptr managing derived object: ");
		inh_poly_4::Base *base_ptr1 = new inh_poly_4::Derived;
		double result = base_ptr1->add();
		fmt::println("Result (base ptr) : {}", result);// 12


		fmt::println("\nBase ref managing derived object: ");
		inh_poly_4::Derived derived1;
		inh_poly_4::Base &base_ref1 = derived1;
		result = base_ref1.add();
		fmt::println("Result (base ref) : {}", result);// 12


		fmt::println("\nRaw base object: ");
		inh_poly_4::Base base3;
		result = base3.add();
		fmt::println("raw result : {}", result);


		// Direct object : Uses static binding
		fmt::println("\nRaw derived object: ");
		inh_poly_4::Derived derived2;
		result = derived2.add();
		fmt::println("Result (Direct object) : {}", result);// 22


		fmt::println("\nRaw objects assignment - slicing: ");
		inh_poly_4::Base base1 = derived2;
		result = base1.add();
		fmt::println("Result (Raw objects assignment) : {}", result);// 11
}