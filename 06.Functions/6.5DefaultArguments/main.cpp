#include <iostream>
#include <string>
#include <string_view>
#include <print>

// A parameter can have a DEFAULT value, used when the caller omits that
// argument. Rules:
//   - defaults go in the PROTOTYPE (the declaration), written once
//   - only TRAILING parameters may have defaults
//   - callers fill arguments left to right; you cannot skip a middle one

std::string greet(std::string_view name,
    std::string_view greeting = "Hello",
    char ponctuation = '!');


int main(){
    
    std::println("{}", greet("Sara"));
    std::println("{}", greet("Sara", "Welcome"));
    std::println("{}", greet("Sara", "Goodbye", '.')); // Goodbye, Sara.

}


// The definition does NOT repeat the defaults.
std::string greet(std::string_view name, 
    std::string_view greeting,
    char punctuation) {
    return std::string{ greeting } + ", " + std::string{ name } + punctuation;
}