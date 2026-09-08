#include <print>

// SCOPE = the region of code where a name is visible.
// LIFETIME = how long the object exists.

int x{1};   // GLOBAL: visible from here to the end of the file

void use_local() {
    int x{25};   // LOCAL: a fresh x each call, gone when the call returns
    std::println("  use_local: x is {} on entry", x);
    ++x;
    std::println("  use_local: x is {} on exit", x);
}

void use_static_local() {
    static int x{50};   // created ONCE, on the first call; kept between calls
    std::println("  use_static_local: x is {} on entry", x);
    ++x;
    std::println("  use_static_local: x is {} on exit", x);
}

void use_global() {
    std::println("  use_global: global x is {} on entry", x);
    x *= 10;
    std::println("  use_global: global x is {} on exit", x);
}

int main() {

    std::println("global x in main: {}", x);

    int x{5};   // LOCAL to main - hides the global x inside main
    std::println("main's local x: {}", x);

    {   // a nested block starts a new scope
        int x{7};   // hides both the outer local and the global
        std::println("inner block x: {}", x);
    }

    std::println("main's local x again: {}", x);   // back to 5

    use_local();          // 25 -> 26
    use_static_local();    // 50 -> 51
    use_global();          // 1 -> 10

    use_local();          // 25 -> 26 again (fresh)
    use_static_local();    // 51 -> 52 (remembered)
    use_global();          // 10 -> 100 (remembered)

    return 0;
}
