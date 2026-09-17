#include <iostream>
#include <print>

int main(){
    const std::string name{ "Daniel" };

    // 01. Without break and continue
    /*
    for (int i{ 0 }; i < 10; ++i) {
        std::println("[{}]: Your name is {}", i, name);
    }
    */

    // 02. With break
    /*
    for (int i{ 0 }; i < 10; ++i) {
        if (i == 5) {
            break;
        }
        std::println("[{}]: Your name is {}", i, name);
    }
    std::println("Moving on ...");
    */


    // 03. With continue 
    for (int i{ 0 }; i < 10; ++i) {
        if (i == 5) {
            continue;
        }
        std::println("[{}]: Your name is {}", i, name);
    }
    std::println("Moving on ...");
}