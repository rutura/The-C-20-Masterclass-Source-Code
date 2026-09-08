#include <print>

// Scope = where a name is visible. Lifetime = how long the object lives.

int counter{0};                 // global: visible everywhere below, lives
                                // for the whole program

void show_scopes() {
    int counter{100};           // local: hides the global inside this function
    std::println("  local counter  = {}", counter);
    std::println("  global counter = {}", ::counter);   // :: reaches the global
}

// A `static` local is created once, the first time the function runs,
// and KEEPS its value between calls - unlike an ordinary local, which is
// fresh every call.
void next_id() {
    static int id{0};           // initialised only on the first call
    ++id;
    std::println("  next id = {}", id);
}

int main() {

    std::println("global counter at start = {}", counter);
    ++counter;                   // touches the global

    show_scopes();

    std::println("--- static local keeps its value ---");
    next_id();                   // 1
    next_id();                   // 2
    next_id();                   // 3

    // Block scope: a name declared inside { } is gone after the brace.
    {
        int temp{7};
        std::println("temp inside block = {}", temp);
    }
    // temp is not in scope here

    return 0;
}
