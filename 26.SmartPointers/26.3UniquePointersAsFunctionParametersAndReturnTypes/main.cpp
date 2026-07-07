#include <iostream>
#include <memory>
#include "dog.h"
#include "person.h"


void do_something_with_dog_v1( std::unique_ptr<Dog> d){
    d->print_info() ;
}


void do_something_with_dog_v2( const std::unique_ptr<Dog>& d){
    d->set_dog_name("Rior");
    d->print_info();
   // d.reset(); // Compiler error
}


std::unique_ptr<Dog> get_unique_ptr(){
    std::unique_ptr<Dog> p_dog = std::make_unique<Dog>("Function Local");
	std::cout << "unique_ptr address(in) : " << &p_dog << std::endl;
    return p_dog;  // The compiler does some optimizations and doesn't return a copy here
					// it's returning something like a reference to the local object.
					// We can prove this by looking at the address of objects in memory.
					// This is not standard behavior, some compilers may actually return 
					// by value by making a copy. The compilers have some freedom to choose
					// their own way to do things.
}

int main(){

    /*
	//Passing unique ptr to functions by value
	std::unique_ptr<Dog> p_dog_1 = std::make_unique<Dog>("Dog1");
    
	//Can't pass unique_ptr by value to a function : copies not allowed
    //do_something_with_dog_v1(p_dog_1);   // copy detected,


	//do_something_with_dog_v1(std::move(p_dog_1)); // Ownership will move to the body
												// of the function and memory will be
												// released when function returns.
												// Not what you typically want.

    std::cout << "p_dog_1 : " << p_dog_1.get() << std::endl; 
    std::cout << "Hitting back the main function" << std::endl;

    */

    std::cout << "------" << std::endl;

    //std::unique_ptr<Dog> p_dog_1 = std::make_unique<Dog>("Dog1");

    /*
    Person person1("John");
    person1.adopt_dog(std::move(p_dog_1)); // The same behavior when function is part of the class
    std::cout << "Doing something , p_dog_1 points to :  " <<p_dog_1.get() <<  std::endl;
    */

	//An implicit move is done when object is created in place as a temporary
	//do_something_with_dog_v1(std::make_unique<Dog>("Temporary Dog"));

//---------------------------------------------------------------------------
    /*
	//Can pass the std::unique_ptr parameter by reference.
	std::unique_ptr p_dog_2 = std::make_unique<Dog>("Dog2");
	p_dog_2->print_info();
	do_something_with_dog_v2(p_dog_2);
	std::cout << "-----" << std::endl;
	p_dog_2->print_info();
    */


//---------------------------------------------------------------------------
	//Returning unique ptr from function by value
/*
	std::unique_ptr<Dog> p_dog_3 = get_unique_ptr();
	std::cout << "delimiter" << std::endl;
	std::cout << "unique_ptr address(out) : " << &p_dog_3 << std::endl;

	 p_dog_3->print_info();
*/

    get_unique_ptr()->print_info();

    std::cout << "function done" << std::endl;
    
	
	
	
	
	


   
    return 0;
}