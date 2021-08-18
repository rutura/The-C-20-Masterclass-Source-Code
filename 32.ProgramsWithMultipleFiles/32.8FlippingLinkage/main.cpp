#include <iostream>

//internal linkage -> external linkage 
extern const double distance {45.7}; 

void print_distance(); // Declaration
void some_other_function(); // Declaration



int main(){

 	std::cout << "distance(main) : " << distance << std::endl;
	std::cout << "&distance(main) : " << &distance << std::endl;
	
	std::cout << std::endl;
	print_distance();

    std::cout << "----" << std::endl;
    some_other_function();
    return 0;
}