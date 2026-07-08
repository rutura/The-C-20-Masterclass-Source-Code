#include <iostream>
#include "dog.h"

int main(){

    Dog dog1("Fluffy","Shepherd",2);
    dog1.print_info(); //1
    dog1.print_info();//2

    for(size_t i{0}; i <10;++i){
        dog1.print_info();
    }

    return 0;
}