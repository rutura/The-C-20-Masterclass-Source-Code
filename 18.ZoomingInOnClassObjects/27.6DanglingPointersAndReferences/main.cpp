#include <iostream>
#include "dog.h"

int main(){

    Dog dog1("Fluffy","Shepherd",2);

    /*
    const std::string& str_ref = dog1.compile_dog_info();
    std::cout << " info : " << str_ref << std::endl;
    */

   unsigned int* int_ptr = dog1.jumps_per_minute();
   std::cout << "jumps_per_minute : " << *int_ptr << std::endl;

    std::cout << "Done!" << std::endl;
    return 0;
}