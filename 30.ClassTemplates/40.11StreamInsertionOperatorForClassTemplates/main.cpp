#include <iostream>
#include "boxcontainer.h"



int main(){

    BoxContainer<int> int_box;
    int_box.add(1);
    int_box.add(2);
    int_box.add(10);
    int_box.add(15);

    std::cout << "int_box : " << int_box << std::endl;
   
    return 0;
}