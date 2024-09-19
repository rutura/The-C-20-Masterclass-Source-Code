#include "utilities.h"

#include "dog.h"

#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }


void const_objects()
{
  const Dog dog1("Fluffy", "Shepherd", 2);

  // Direct access
  /*
  dog1.print_info(); // Compiler error

  dog1.set_name("Milou"); // Compiler error

  dog1.print_info();
  */

  // Pointer to non const
  // Dog * dog_ptr = &dog1;

  // Non const reference
  // Dog& dog_ref = dog1;

  // Pointer to const
  const Dog *const_dog_ptr = &dog1;
  // const_dog_ptr->set_name("Milou"); // Expect
  // const_dog_ptr->get_name();

  // Const reference
  const Dog &const_dog_ref = dog1;
  // const_dog_ref.set_name("Milou"); // Expected
  // const_dog_ref.get_name();
}


//Exploring const objects as function parameters
/*
// This causes no problem because we are working with
// a copy inside the function
void function_taking_dog(Dog dog)
{
  dog.set_name("Internal dog");
  dog.print_info();
}

// Parameter by reference
void function_taking_dog_ref(Dog &dog_ref)
{
  // Compiler won't allow passing const object as argument
}

// Parameter by const reference
void function_taking_const_dog_ref(const Dog &const_dog_ref)
{
  // const_dog_ref.set_name("Hillo"); //Expected
  // const_dog_ref.print_info(); // Error
}

// Pointer to non const as parameter
void function_taking_dog_p(Dog *p_dog)
{
  // Compiler won't allow passing const Dog objects as arguments
}

// Parameter passed as pointer to const
void function_taking_pointer_to_const_dog(const Dog *const_p_dog)
{
  //	const_p_dog->set_name("Hillo");//Error : Expected
  //	const_p_dog->print_info(); //Error : Not expected
}



void const_objects_as_function_parameters(){
	//const Dog dog1("Fluffy", "Shepherd", 2);
	//fmt::println("address of object : {}", fmt::ptr(&dog1));

	// Function taking parameter by value : WORKS
	// function_taking_dog(dog1);

	// function_taking_dog_ref(dog1); // Compiler error

	// function_taking_const_dog_ref(dog1);

	// function_taking_dog_p(&dog1);

	// function_taking_pointer_to_const_dog(&dog1);
}
*/

//THE ABOVE BLOCK SHOULD BE COMMENTED OUT BEFORE YOU WORK ON CONST MEMBER FUNCTIONS
//Const member functions
/*

// This causes no problem because we are working with
// a copy inside the function
void function_taking_dog(Dog dog)
{
  dog.set_name("Internal dog");
  dog.print_info();
}

// Parameter by reference
void function_taking_dog_ref(Dog &dog_ref)
{
  // Compiler won't allow passing const object as argument
}

// Parameter by const reference
void function_taking_const_dog_ref(const Dog &const_dog_ref)
{
  // const_dog_ref.set_name("Hillo"); //Expected
  const_dog_ref.print_info();
}

// Pointer to non const as parameter
void function_taking_dog_p(Dog *p_dog)
{
  // Compiler won't allow passing const Dog objects as arguments
}

// Parameter passed as pointer to const
void function_taking_pointer_to_const_dog(const Dog *const_p_dog)
{
  // const_p_dog->set_name("Hillo");//Error : Expected
  const_p_dog->print_info();
}

void const_member_functions(){
	const Dog dog1("Fluffy", "Shepherd", 2);

	dog1.print_info();

	// Function taking parameter by value : WORKS
	// function_taking_dog(dog1);

	// function_taking_dog_ref(dog1); // Compiler error

	// function_taking_const_dog_ref(dog1);

	// function_taking_dog_p(&dog1);

	//function_taking_pointer_to_const_dog(&dog1);
}
*/


//Mutable objects
void mutable_objects()
{
  Dog dog1("Fluffy", "Shepherd", 2);
  dog1.print_info();// 1
  dog1.print_info();// 2

  for (size_t i{ 0 }; i < 10; ++i) { dog1.print_info(); }

}