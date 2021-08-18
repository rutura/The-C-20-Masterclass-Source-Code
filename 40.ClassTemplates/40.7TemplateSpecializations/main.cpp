#include <iostream>
#include "adder.h"


int main(){

    Adder<int> adder_int;
	adder_int.do_something();
    std::cout << adder_int.add(10,20) << std::endl;

    std::cout << "-------" << std::endl;

    //Char*
    char str1[20] {"Hello"};
    char str2[] {" World!"};
    
    Adder<char*> adder_c_str;
	//adder_c_str.do_something();
    std::cout << adder_c_str.add(str1,str2) << std::endl;
   
    return 0;
}