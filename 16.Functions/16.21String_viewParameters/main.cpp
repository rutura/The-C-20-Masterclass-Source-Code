#include <fmt/format.h>
#include <string_view>

void say_my_name(std::string_view name){
    fmt::println( "Hello your name is : {}", name );
}

int main(){

    std::string some_name{"John"};
    //say_my_name("John");
    //say_my_name(some_name);
    say_my_name(std::string_view("Samuel"));
   
    return 0;
}