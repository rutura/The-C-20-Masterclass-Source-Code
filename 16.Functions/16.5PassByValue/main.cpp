#include <fmt/format.h>

void say_age(int age){ // Parameter
    ++age;
    fmt::println(  "Hello , you are {} years old! &age : {}", age,  fmt::ptr(&age) );
}

int main(){

    int age{23}; // Local
    fmt::println( "age (before call) : {} &age : {}" ,age,  fmt::ptr(&age) );
    say_age(age); // Argument
    fmt::println( "age (after call) : {} &age : {}", age,  fmt::ptr(&age) );

    return 0;
}