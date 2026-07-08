#include <print>

void say_age(int* age);             // pointer to modifiable data - can change the caller's value
void say_age_const(const int* age); // pointer to const data - read-only through this pointer
void say_age_const_ptr(const int* const age); // both the pointer and the pointed-to data are const

int main() {

    int age{23};
    std::println("age (before call) : {} &age : {}", age, static_cast<const void*>(&age));
    say_age(&age); // the caller must explicitly pass the address
    std::println("age (after call) : {} &age : {}", age, static_cast<const void*>(&age));

    std::println("");
    age = 23;
    say_age_const(&age);
    std::println("age (after const call) : {}", age); // unchanged - say_age_const can't modify it

    std::println("");
    say_age_const_ptr(&age);

    // print_sum below takes two int* parameters directly - passing
    // addresses in is the whole "conversion," there's no implicit
    // conversion happening beyond that.
    int a{3};
    int b{12};
    std::println("");
    std::println("sum : {}", *(&a) + *(&b));

    return 0;
}

void say_age(int* age) {
    ++(*age);
    std::println("Hello, you are {} years old! &age : {}", *age, static_cast<const void*>(age));
}

void say_age_const(const int* age) {
    // ++(*age); // compiler error: age points to const data
    std::println("Hello, you are {} years old! &age : {}", *age, static_cast<const void*>(age));
}

void say_age_const_ptr(const int* const age) {
    // ++(*age); // compiler error: pointed-to data is const
    std::println("Hello, you are {} years old! &age : {}", *age, static_cast<const void*>(age));
    // age = &some_other_int; // compiler error: age itself is also const, can't be repointed
}
