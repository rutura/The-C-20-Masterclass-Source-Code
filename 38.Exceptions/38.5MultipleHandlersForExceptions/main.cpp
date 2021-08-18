#include <iostream>

//Declarations
void f1();
void f2();
void f3();

void exception_thrower(){
    std::cout << "starting exception_thrower()" << std::endl;
    throw 0;// Execution will half from here
    std::cout << "ending exception_thrower()" << std::endl;
}


int main(){

    try{
        f1();
    }catch(int ex){
        std::cout << "Handling execution in main()" << std::endl;        
    }
    std::cout << "main() finishing up" << std::endl;
   
    return 0;
}

//Definitions

void f1(){
    std::cout << "Starting f1()" << std::endl;
    try{
        f2();
    }catch(int ex){
        std::cout << "Exception handled in f1()" << std::endl;
    }
    std::cout << "Ending f1()" << std::endl;
}

void f2(){
    std::cout << "Starting f2()" << std::endl;
    try{
        f3();
    }catch(int ex){
        std::cout << "Exception handled in f2()" << std::endl;
    }
    std::cout << "Ending f2()" << std::endl;    
}

void f3(){
    std::cout << "Starting f3()" << std::endl;
    try{
        exception_thrower();
    }catch(int ex){
        std::cout << "Exception handled in f3()" << std::endl;
    }
    std::cout << "Ending f3()" << std::endl;    
}