#include <print>

int main() {

    using HugeInt = unsigned long long int; // modern alias syntax
    // typedef unsigned long long int HugeInt; // older, pre-C++11 syntax - same effect

    HugeInt huge_number{123'378'997};

    std::println("sizeof(unsigned long long int) : {}", sizeof(unsigned long long int));
    std::println("sizeof(HugeInt) : {}", sizeof(HugeInt));
    std::println("huge_number : {}", huge_number);

    return 0;
}