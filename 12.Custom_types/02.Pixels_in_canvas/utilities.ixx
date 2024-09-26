module;

#include <fmt/format.h>
#include <memory>


export module utilities; 

import canvas;

export void canvas_demo(){
	
	// Create a canvas and set a pixel at (5, 5) on the stack.
	/*
	raw::Canvas canvas{10, 10};
	Pixel pixel(0xFF0000, Position{5, 5});
	canvas.set_pixel_at(5, 5, pixel);
	canvas.print();
	*/

	// Create a canvas and set a pixel at (5, 5) on the heap, with smart pointers
	/*
	auto canvas = std::make_unique<raw::Canvas>{10, 10};
	auto pixel = std::make_unique<Pixel>(0xFF0000, Position{5, 5});
	canvas->set_pixel_at(5, 5, *pixel);
	canvas->print();
	*/

	//Create a canvas and set a pixel at (5, 5) on the heap using raw pointers.
	/*
	auto canvas = new raw::Canvas{10, 10};
	auto pixel = new Pixel(0xFF0000, Position{5, 5});
	canvas->set_pixel_at(5, 5, *pixel);
	canvas->print();
	delete pixel;
	delete canvas;
	*/

	//Use the assignment operator and print the canvas. Use smart pointers.
	/*
	auto canvas = std::make_unique<raw::Canvas>(10, 10);
	auto pixel = std::make_unique<Pixel>(0xFF0000, Position{5, 5});
	canvas->set_pixel_at(5, 5, *pixel);
	canvas->print();

	fmt::println("Before copying");
	auto canvas2 = std::make_unique<raw::Canvas>(10, 10);
	canvas2->print();
	fmt::println("After copying");
	*canvas2 = *canvas;	
	canvas2->print();
	*/

	// Use the entities in the modern namespace
	auto canvas = std::make_unique<modern::Canvas>(10, 10);
	auto pixel = std::make_unique<Pixel>(0xFF0000, Position{5, 5});
	canvas->set_pixel_at(5, 5, *pixel);
	canvas->print();

	fmt::println("Before copying");
	auto canvas2 = std::make_unique<modern::Canvas>(10, 10);
	canvas2->print();
	fmt::println("After copying");
	*canvas2 = *canvas;	
	canvas2->print();
}