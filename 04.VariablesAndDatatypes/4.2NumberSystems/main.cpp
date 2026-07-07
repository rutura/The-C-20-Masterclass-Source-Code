// We are building a small "expense tracker" throughout this chapter,
// one piece at a time - just like the profile program from chapter 3.

#include <print>

int main() {

    // A plain number like this is written in decimal (base 10) - the numbering
    // system we use every day. The digit separator ' ' is just for readability;
    // the compiler ignores it.
    int transactionId{1'000};
    std::println("Transaction id (decimal): {}", transactionId);

    // A budget tracker often needs to know which spending categories are
    // active this month - food, transport, entertainment, other - packed as
    // individual bits of one integer. The same bit pattern can be written in
    // binary, octal, or hexadecimal; only how it's *spelled* in the source
    // code changes, not the value stored.
    int categoryFlags1{0b0000'1111}; // binary: 0b prefix, one bit per category
    int categoryFlags2{017};         // octal: leading 0
    int categoryFlags3{0x0F};        // hexadecimal: 0x prefix

    std::println("Categories active (binary literal)      : {}", categoryFlags1);
    std::println("Categories active (octal literal)       : {}", categoryFlags2);
    std::println("Categories active (hexadecimal literal) : {}", categoryFlags3);

    // std::format/std::println can also print an existing value back out in
    // whichever base is most useful for reading it - handy when hunting for
    // which category bits are actually set.
    std::println("transactionId as hex   : {:#x}", transactionId);
    std::println("transactionId as octal : {:#o}", transactionId);
    std::println("transactionId as binary: {:#b}", transactionId);

    return 0;
}
