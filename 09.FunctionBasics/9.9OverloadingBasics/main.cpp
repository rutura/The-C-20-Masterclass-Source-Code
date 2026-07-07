#include <print>
#include <string_view>

// Overloading: several functions can share the same name as long as their
// parameter types differ. The compiler picks the right one based on the
// arguments at the call site - this is resolved at compile time, not by
// checking types while the program runs.
int higherOf(int a, int b) {
    std::println("int overload called");
    return (a > b) ? a : b;
}

double higherOf(double a, double b) {
    std::println("double overload called");
    return (a > b) ? a : b;
}

std::string_view higherOf(std::string_view a, std::string_view b) {
    std::println("string_view overload called");
    return (a > b) ? a : b; // compares alphabetically
}

int main() {

    int intResult = higherOf(4, 9);
    double doubleResult = higherOf(5.4, 7.4);
    std::string_view stringResult = higherOf("Apple", "Banana");

    std::println("intResult    : {}", intResult);
    std::println("doubleResult : {}", doubleResult);
    std::println("stringResult : {}", stringResult);

    // A subtlety worth knowing: a plain "int a" parameter and a "const int a"
    // parameter are NOT different enough to count as separate overloads.
    // const here only affects what the function is allowed to do with its
    // own local copy - it's invisible to the caller and to overload
    // resolution, so this would be a compiler error, not a valid overload:
    //
    // int higherOf(int a, int b);
    // int higherOf(const int a, const int b); // error: redefinition

    return 0;
}
