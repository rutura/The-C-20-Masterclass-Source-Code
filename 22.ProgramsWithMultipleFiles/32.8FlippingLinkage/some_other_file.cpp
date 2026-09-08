#include <iostream>
extern const double distance; // Declaration

void print_distance(){
	//++distance; // Error : can't modify a read only variable.
	std::cout << "distance(some_other_file) : " << distance << std::endl;
	std::cout << "&distance(some_other_file) : " << &distance << std::endl;
}

//External linkage -> internal linkage
/*
static void some_other_function(){
    std::cout << "Hello there" << std::endl;
}
*/

//Internal linkage
namespace{
     void some_other_function(){
        std::cout << "Hello there" << std::endl;
    }    
}