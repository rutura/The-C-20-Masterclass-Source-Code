#include <iostream>
#include "child.h"



int main(){
	Child child(33);
    child.print_var();// Calls the method in Child
    child.Parent::print_var(); // Calls the method in Parent, 
                               // value in parent just contains junk or whatever
                               // in class initialization we did.
							   
    std::cout << "--------" << std::endl;
    child.show_values();
    return 0;
}