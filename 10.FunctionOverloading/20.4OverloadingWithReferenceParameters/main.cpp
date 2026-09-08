#include <iostream>
#include <string>

//Ambiguous calls
void say_my_name( const std::string& name){
    std::cout << "Your name is (ref) : " << name << std::endl;
}

void say_my_name( std::string name){
    std::cout << "Your name is (non ref) : " << name << std::endl;
}

//Implicit conversions with references

double max(double a, double b){
    std::cout<< "double max called" << std::endl;
    return (a>b)?a:b;
}


//int& max(int& a, int& b){
const int& max(const int& a,const int& b){
    std::cout << "int max called" << std::endl;
    return (a>b)?a:b;
}

int main(){

    char a{6};
    char b{9};


    auto result = max(a,b);

   
    return 0;
}