/*
    . The content from previous version of the course verbatim.

*/

#include <fmt/format.h>

int main(){

	auto var1 {12};
    auto var2 {13.0};
    auto var3 {14.0f};
    auto var4 {15.0l};
    auto var5 {'e'};
    
    //int modifier suffixes
    auto var6 { 123u}; // unsigned
    auto var7 { 123ul}; //unsigned long
    auto var8 { 123ll}; // long long

    fmt::println("var1 occupies : {} bytes", sizeof(var1));
    fmt::println("var2 occupies : {} bytes", sizeof(var2));
    fmt::println("var3 occupies : {} bytes", sizeof(var3));
    fmt::println("var4 occupies : {} bytes", sizeof(var4));
    fmt::println("var5 occupies : {} bytes", sizeof(var5));
    fmt::println("var6 occupies : {} bytes", sizeof(var6));
    fmt::println("var7 occupies : {} bytes", sizeof(var7));
    fmt::println("var8 occupies : {} bytes", sizeof(var8));
   
    return 0;
}