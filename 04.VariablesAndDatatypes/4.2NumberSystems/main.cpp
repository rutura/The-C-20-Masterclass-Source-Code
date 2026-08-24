#include <iostream>
#include <print>

int main() {

    // The same value, written four different ways. The compiler treats
    // all four identically - the prefix only changes how you spell the
    // literal in source code, not what gets stored.
    int decimal{15};        // base 10: the default
    int octal{017};         // base 8: leading 0
    int hexadecimal{0x0F};  // base 16: leading 0x
    int binary{0b00001111}; // base 2: leading 0b

    std::println("decimal     : {}", decimal);
    std::println("octal       : {}", octal);
    std::println("hexadecimal : {}", hexadecimal);
    std::println("binary      : {}", binary);

    // std::println's format spec can also print an existing value back
    // out in a different base - handy when you want to see what a
    // decimal number looks like in another base.
    int reading{1024};
    std::println("{} in decimal is {}, octal {:#o}, hex {:#x}, binary {:#b}",
        reading, reading, reading, reading, reading);

    // The std::cout equivalent: std::dec/std::oct/std::hex switch the
    // base for everything printed afterward, and that base sticks until
    // changed again - so we switch back to std::dec at the end to leave
    // std::cout in its default state for whatever prints next. There's
    // no std::bin manipulator at all - binary output just isn't
    // something std::cout can do without extra work.
    std::cout << reading << " in decimal is " << std::dec << reading
        << ", octal " << std::oct << reading
        << ", hex " << std::hex << reading
        << std::dec << "\n";

    return 0;
}
