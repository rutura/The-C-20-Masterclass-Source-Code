#include <iostream>
#include "utility.h"

 inline int age{12};

 inline void some_function(){
	std::cout << "age : " << age << std::endl;
	std::cout << "&age : " << &age << std::endl;
}

void print_age_utility1(){
    std::cout << "Printing from utility1 : " << std::endl;
    some_function();
    std::cout << std::endl;
}

