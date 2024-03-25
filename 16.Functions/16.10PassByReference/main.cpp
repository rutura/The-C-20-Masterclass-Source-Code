#include <fmt/format.h>

void say_age(int& age); // Declaration

int main(){

    int age{23}; // Local
    fmt::println( "age (before call) : {} &age : {}", age, fmt::ptr(&age) ); //23
    say_age(age); // Argument
    fmt::println( "age (after call) : {} &age : {}", age,  fmt::ptr(&age) ); //24

    return 0;
}


void say_age(int& age){ // Parameter
    ++age; 
    fmt::println(  "Hello , you are {} years old! &age : {}", age, fmt::ptr(&age) );//24

}