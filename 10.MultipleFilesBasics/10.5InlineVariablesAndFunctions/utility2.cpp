#include <iostream>

 inline int age{12};

 inline void some_function(){
	std::cout << "age : " << age << std::endl;
	std::cout << "&age : " << &age << std::endl;
}

void print_age_utility2(){
    std::cout << "Printing from utility2 : " << std::endl;
    some_function();
    std::cout << std::endl;
}


