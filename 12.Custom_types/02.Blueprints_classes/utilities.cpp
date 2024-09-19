#include "utilities.h"

#include "outer.h"
#include "cylinder.h"
#include "dog.h"

#include <fmt/format.h>


void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

//Your first class
/*
void your_first_class(){
	Cylinder cylinder1;// Objects
	fmt::println("volume : {}", cylinder1.volume());

	// Change the member variables
	cylinder1.base_radius = 10;
	cylinder1.height = 3;

	fmt::println("volume : {}", cylinder1.volume());

	cylinder1.height = 8;

	fmt::println("volume : {}", cylinder1.volume());
}
*/


//Using constructors
/*
void using_constructors(){
	// Cylinder cylinder1(10,4); // Object
	Cylinder cylinder1;
	fmt::println("volume : {}", cylinder1.volume());
}
*/

//Defaulted constructors
/*
void defaulted_constructors(){
	Cylinder cylinder1;
	fmt::println("volume : {}", cylinder1.volume());
}
*/


//Setters and getters
/*
void setters_and_getters(){
	Cylinder cylinder1(10, 10);
	fmt::println("volume : {}", cylinder1.volume());

	// Modify our object
	cylinder1.set_base_radius(100);
	cylinder1.set_height(10);

	fmt::println("volume : {}", cylinder1.volume());
}
*/


//Class across multiple files
void class_x_multiple_files(){
    Cylinder cylinder1(10, 10);
    fmt::println("volume : {}", cylinder1.volume());
}

void order_of_constr_destr_calls(){
    Dog dog1("Dogyy1", "Shepherd", 2);
    Dog dog2("Dogyy2", "Shepherd", 3);
    Dog dog3("Dogyy3", "Shepherd", 5);
    Dog dog4("Dogyy4", "Shepherd", 1);
}

void nested_classes(){
    Outer outer1(10, 20.1);
    outer1.do_something();
}