#include <iostream>
#include <string_view>

void say_my_name(std::string_view name){
    std::cout << "Hello your name is : " << name << std::endl;
}

int main(){

    std::string some_name{"John"};
    //say_my_name("John");
    //say_my_name(some_name);
    say_my_name(std::string_view("Samuel"));
   
    return 0;
}