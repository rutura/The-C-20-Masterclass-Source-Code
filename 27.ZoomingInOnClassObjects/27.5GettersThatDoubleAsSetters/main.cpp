#include <iostream>
#include "dog.h"

int main(){

   const Dog dog1("Fluffy","Shepherd",2);
   dog1.print_info();
   std::cout << "dog name : " << dog1.name() << std::endl; // Getter

   //Modify the object
   //dog1.name() = "Milou"; // Setter
   dog1.print_info();




    return 0;
}