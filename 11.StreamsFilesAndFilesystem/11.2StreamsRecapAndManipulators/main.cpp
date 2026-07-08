// You've been using streams since chapter 3: std::cin >> reads from the
// standard input stream, and std::print/std::println write to the standard
// output stream under the hood. A "stream" is just a sequence of characters
// flowing in or out of somewhere - the console, a string, or (starting next
// lecture) a file. This chapter is about the other places that sequence can
// flow to and from.
//
// Before std::format existed, the only way to control how a stream printed
// a value - width, alignment, precision, base - was to push manipulators
// into it with <<. You'll still see this style in older/existing code, so
// it's worth recognizing even though std::format's mini-language (chapter 5)
// is the more readable modern choice for new code.

#include <print>
#include <iostream>
#include <iomanip>

int main() {

    double price{9.5};
    int quantity{7};

    // The format-string equivalent of everything below:
    std::println("std::format equivalent : {:>10.2f} | {:#x} | {}", price, quantity, true);

    // std::setprecision + std::fixed: how many digits after the decimal point.
    // Manipulators are "sticky" - once set on a stream, they apply to every
    // subsequent << until changed again, unlike a std::format call which only
    // affects that one call.
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "price with std::setprecision(2) : " << price << '\n';

    // std::setw only affects the *next* single value, then resets - the one
    // manipulator here that isn't sticky.
    std::cout << "right-aligned in a width of 10 : [" << std::setw(10) << price << "]\n";
    std::cout << "left-aligned in a width of 10  : [" << std::left << std::setw(10) << price << "]\n";
    std::cout << std::right; // undo the stickiness of std::left for what follows

    // std::hex/std::oct change the base numbers print in - also sticky.
    std::cout << "quantity in hex : " << std::hex << quantity << '\n';
    std::cout << "quantity in oct : " << std::oct << quantity << '\n';
    std::cout << std::dec; // back to decimal

    // std::boolalpha prints true/false instead of 1/0.
    bool inStock{true};
    std::cout << "inStock as 1/0        : " << inStock << '\n';
    std::cout << "inStock with boolalpha: " << std::boolalpha << inStock << '\n';

    return 0;
}
