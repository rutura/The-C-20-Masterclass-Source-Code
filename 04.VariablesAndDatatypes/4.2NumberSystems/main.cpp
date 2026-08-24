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
    // decimal number looks like in hex or binary.
    int reading{1024};
    std::println("{} in hex is {:#x} and in binary is {:#b}", reading, reading, reading);

    return 0;
}
