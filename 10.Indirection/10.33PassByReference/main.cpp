#include <print>

void say_age(int& age); // declaration

int main() {

    int age{23}; // local
    std::println("age (before call) : {} &age : {}", age, static_cast<const void*>(&age));
    say_age(age); // no & needed at the call site - the reference binding happens in the signature
    std::println("age (after call) : {} &age : {}", age, static_cast<const void*>(&age));

    return 0;
}

void say_age(int& age) { // parameter - a reference to the caller's age, not a copy
    ++age;
    std::println("Hello, you are {} years old! &age : {}", age, static_cast<const void*>(&age));
}
