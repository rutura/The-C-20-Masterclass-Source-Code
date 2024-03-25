#include <fmt/format.h>

int main(){

     using HugeInt = unsigned long long int; // Recommended in modern C++
     //typedef unsigned long long int HugeInt; // Older C++ syntax for type aliases
     HugeInt huge_number {123378997};

     fmt::println( "sizeof(unsigned long long int ) : {}" , sizeof(unsigned long long int) );
     fmt::println( "sizeof(HugeInt) : {}" , sizeof(HugeInt) );

    fmt::println( "huge_number : {}" , huge_number );

    return 0;
}