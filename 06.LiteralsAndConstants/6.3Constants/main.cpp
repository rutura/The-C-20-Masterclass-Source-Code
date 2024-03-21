#include <iostream>
#include <fmt/format.h>

/*
 * Changed the outputs stream to fmt's
 */
int main(){
    const int age {34};
    const float height {1.67f};

    //age = 55; // Can't modify
    //height = 1.8f;

    int years { 3 * age};
    fmt::println("Age:{}, Height:{}, Years: {}", age, height, years);

    return 0;
}