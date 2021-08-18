#include <iostream>
#include "dog.h"

//This causes no problem because we are working with 
//a copy inside the function
void function_taking_dog(Dog dog){
	dog.set_name("Internal dog");
	dog.print_info();
}

//Parameter by reference
void function_taking_dog_ref(Dog& dog_ref){
	//Compiler won't allow passing const object as argument
}

//Parameter by const reference
void function_taking_const_dog_ref(const Dog& const_dog_ref){
	//const_dog_ref.set_name("Hillo"); //Expected
	const_dog_ref.print_info(); 
}

//Pointer to non const as parameter
void function_taking_dog_p(Dog* p_dog){
	//Compiler won't allow passing const Dog objects as arguments
}

//Parameter passed as pointer to const
void function_taking_pointer_to_const_dog(const Dog* const_p_dog){
	//const_p_dog->set_name("Hillo");//Error : Expected
	const_p_dog->print_info(); 
}


int main(){

    const Dog dog1("Fluffy","Shepherd",2);

    dog1.print_info();

    //Function taking parameter by value : WORKS
    //function_taking_dog(dog1);

    //function_taking_dog_ref(dog1); // Compiler error

    //function_taking_const_dog_ref(dog1);

    //function_taking_dog_p(&dog1);

    function_taking_pointer_to_const_dog(&dog1);


    return 0;
}