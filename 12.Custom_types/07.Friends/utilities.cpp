#include "utilities.h"

#include "dog.h"

#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


// #1: Friend functions
/*
void friend_functions(){
	Dog dog1("Fluffy", 4);
	debug_dog_info(dog1);

	//debug_dog_info();
}
*/


// #2: Friend classes
void friend_classes(){

	Cat cat1;
	Dog dog1("Fluffly", 2);
	cat1.print_dog_info(dog1);
}