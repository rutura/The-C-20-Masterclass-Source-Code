// We are building a small "arcade high-score tracker" throughout this chapter,
// one piece at a time - just like the profile program from chapter 3.

#include <print>

int main() {

    // A plain number like this is written in decimal (base 10) - the numbering
    // system we use every day. The digit separator ' ' is just for readability;
    // the compiler ignores it.
    int highScore{1'000'000};
    std::println("High score (decimal): {}", highScore);

    // Arcade cabinets often pack several yes/no flags - extra life, shield,
    // double points, invincibility - into the individual bits of one integer.
    // The same bit pattern can be written in binary, octal, or hexadecimal;
    // only how it's *spelled* in the source code changes, not the value stored.
    int powerUpFlags1{0b0000'1111}; // binary: 0b prefix, one bit per power-up
    int powerUpFlags2{017};         // octal: leading 0
    int powerUpFlags3{0x0F};        // hexadecimal: 0x prefix

    std::println("Power-ups (binary literal)      : {}", powerUpFlags1);
    std::println("Power-ups (octal literal)       : {}", powerUpFlags2);
    std::println("Power-ups (hexadecimal literal) : {}", powerUpFlags3);

    // std::format/std::println can also print an existing value back out in
    // whichever base is most useful for reading it - handy when hunting for
    // which power-up bits are actually set.
    std::println("highScore as hex   : {:#x}", highScore);
    std::println("highScore as octal : {:#o}", highScore);
    std::println("highScore as binary: {:#b}", highScore);

    return 0;
}
