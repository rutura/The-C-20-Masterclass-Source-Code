#include "dog.h"

// Passing by value works regardless of const-correctness: the function
// receives its own copy, so the caller's const object is untouched either way.
void function_taking_dog(Dog dog){
	dog.set_name("Internal dog");
	dog.print_info();
}

// Passing a non-const reference/pointer to a const object is rejected by the
// compiler outright - it would let the function bypass constness entirely.
void function_taking_dog_ref(Dog& dog_ref){
	//Compiler won't allow passing a const Dog object as this argument
}
void function_taking_dog_p(Dog* p_dog){
	//Compiler won't allow passing a const Dog object as this argument
}

// A const reference/pointer parameter is where const-correctness actually
// matters: without const member functions, EVERY call below would fail to
// compile, even the read-only ones - the compiler can't tell get_name() or
// print_info() won't modify the object unless the member function itself
// promises not to (dog.h marks them const for exactly this reason).
void function_taking_const_dog_ref(const Dog& const_dog_ref){
	//const_dog_ref.set_name("Hillo"); // Error (expected): set_name isn't const
	const_dog_ref.print_info(); // Works: print_info() is a const member function
}
void function_taking_pointer_to_const_dog(const Dog* const_p_dog){
	//const_p_dog->set_name("Hillo"); // Error (expected): set_name isn't const
	const_p_dog->print_info(); // Works: print_info() is a const member function
}


int main(){

    const Dog dog1("Fluffy","Shepherd",2);

    // Calling a const member function on a const object: works.
    dog1.print_info();

    // dog1.set_name("Rex"); // Error: set_name() isn't const, dog1 is

    function_taking_dog(dog1);
    //function_taking_dog_ref(dog1); // Compiler error: non-const ref from const object
    function_taking_const_dog_ref(dog1);
    //function_taking_dog_p(&dog1); // Compiler error: non-const pointer from const object
    function_taking_pointer_to_const_dog(&dog1);

    return 0;
}
