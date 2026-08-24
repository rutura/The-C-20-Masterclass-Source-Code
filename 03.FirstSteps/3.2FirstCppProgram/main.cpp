#include <iostream>
#include <print>

// This is a one-line comment: the compiler ignores everything after //.

/*
    This is a block comment. It can span multiple lines and is handy
    for longer explanations.
*/

int main() {

    // The traditional way to print in C++: chain values onto std::cout
    // with <<. This is what you'll see in most existing C++ code and
    // tutorials, so it's worth recognizing even though we won't use it
    // much going forward.
    std::cout << "Hello, C++!\n";
    std::cout << "This is the classic way to print output.\n";

    // C++23 gives us std::println: no chaining, no manual "\n" juggling,
    // and it supports {}-style formatting like Python or Rust. This is
    // what we'll use for the rest of the course.
    std::println("Hello, C++!");
    std::println("This is the modern way to print output.");

    std::string name{"Ada"};
    int age{28};
    std::println("{} is {} years old.", name, age);

    // A compile-time error: uncomment to see the compiler refuse to build.
    // The mistake is caught before the program ever runs.
    // std::println("{} has a typo)", name);

    // A run-time error: this compiles fine, but crashes/misbehaves when
    // the program actually executes this line - the compiler can't catch
    // every mistake, only the ones it understands statically.
    // int total{7 / 0};
    // std::println("total: {}", total);

    return 0;
}
