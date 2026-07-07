#include <iostream>

//Declarations
void print_age(int age = 33);

void print_age(long int age = 44);

int main(){


    print_age();
    
    
    return 0;
}

//Definitions
void print_age(int age ){
    std::cout << "Your age is( int version)  : " << age << std::endl;
}

void print_age(long int age){
    std::cout << "Your age is (long int version) : " << age << std::endl;
}
