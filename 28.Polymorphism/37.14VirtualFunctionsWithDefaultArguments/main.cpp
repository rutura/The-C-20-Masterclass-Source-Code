#include <iostream>
#include "derived.h"

int main(){

    //Base ptr : Uses polymorphism
    Base * base_ptr1 = new Derived;
    double result = base_ptr1->add();
    std::cout <<"Result (base ptr) : " << result  << std::endl; //12


    std::cout << "---------------------"<< std::endl;
	
    //Base ref : Uses Polymorphism
    Derived derived1;
    Base& base_ref1 = derived1;
    result = base_ref1.add();
    std::cout << "Result (base ref) : " << result << std::endl; // 12
    
    std::cout << "---------------------"<< std::endl;


    //Raw objects
    Base base3;
    result = base3.add();
    std::cout << "raw result : " << result << std::endl;

    std::cout << "---------------------"<< std::endl;

    //Direct object : Uses static binding
    Derived derived2;
    result = derived2.add();
    std::cout << "Result (Direct object) : " << result << std::endl; // 22
	
    std::cout << "---------------------"<< std::endl;

	//Raw objects - slicing : uses static binding
	Base base1 = derived2;
	result = base1.add();
    std::cout << "Result (Raw objects assignment) : " << result << std::endl; //11

   
    return 0;
}