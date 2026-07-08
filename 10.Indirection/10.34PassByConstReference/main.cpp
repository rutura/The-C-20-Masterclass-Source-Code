#include <print>

void say_age(const int& age); // declaration

int main() {

    int age{23}; // local
    std::println("age (before call) : {} &age : {}", age, static_cast<const void*>(&age));
    say_age(age);
    std::println("age (after call) : {} &age : {}", age, static_cast<const void*>(&age));

    return 0;
}

void say_age(const int& age) { // parameter - avoids a copy, but can't modify the caller's age
    // ++age; // compiler error: age is const here
    std::println("Hello, you are {} years old! &age : {}", age, static_cast<const void*>(&age));
}
