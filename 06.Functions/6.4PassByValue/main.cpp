#include <print>

// Pass by value: the parameter is a COPY of the argument. The function
// works on its own copy, so changes to the parameter do NOT affect the
// caller's variable.

void try_to_grow(int age) {
    ++age;                       // changes this function's copy only
    std::println("  inside try_to_grow: age = {}", age);
}

int main() {

    int my_age{23};

    std::println("before call: my_age = {}", my_age);
    try_to_grow(my_age);         // my_age is copied into the parameter
    std::println("after call : my_age = {}", my_age);   // unchanged - still 23

    // The copy is a separate object: it even lives at a different address.
    // (Addresses print as hex; the point is only that they differ.)

    return 0;
}
