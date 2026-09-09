#include <print>

// When a local variable HIDES a global with the same name, the local
// wins inside its scope. The UNARY SCOPE RESOLUTION OPERATOR, ::name,
// reaches past the local to the global.

int value{7};        // global

int main() {

    double value{10.5};   // local - hides the global `value` in main

    std::println("local  value  = {}", value);     // the local double
    std::println("global ::value = {}", ::value);   // the global int, reached with ::

    return 0;
}
