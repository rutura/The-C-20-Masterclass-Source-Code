#include <iostream>
#include "dog.h"


int main(){

    const Dog dog1("Fluffy","Shepherd",2);

    //Direct access
    /*
    dog1.print_info(); // Compiler error

    dog1.set_name("Milou"); // Compiler error

    dog1.print_info();
    */

   //Pointer to non const
   //Dog * dog_ptr = &dog1;

   //Non const reference
   //Dog& dog_ref = dog1;

   //Pointer to const
   const Dog* const_dog_ptr = &dog1;
   //const_dog_ptr->set_name("Milou"); // Expect
   //const_dog_ptr->get_name();

   //Const reference
   const Dog& const_dog_ref = dog1;
   //const_dog_ref.set_name("Milou"); // Expected
   //const_dog_ref.get_name();

    return 0;
}