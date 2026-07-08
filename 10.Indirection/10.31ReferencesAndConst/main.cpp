#include <print>

int main() {

    std::println("");
    std::println("Const reference : ");
    int age{27};
    const int& ref_age{age};

    std::println("age : {}", age);
    std::println("ref_age : {}", ref_age);

    // A const reference can't modify what it's bound to - ref_age++ here
    // would be a compiler error ("increment of read-only reference"),
    // exactly like *p_age = ... would be through a pointer-to-const.
    // ref_age++;

    // Simulating the same restriction with a pointer instead:
    // const int* const p_age {&age};
    // *p_age = 45;

    return 0;
}
