// Older C++ controlled output with std::cout <<  manipulators (std::setw,
// std::fixed, std::hex, ...) which mutate hidden state on the stream itself -
// a setting like std::hex silently stays on for every << that follows until
// something turns it back off. C++20's std::format (and C++23's
// std::println, used throughout this course) replace nearly all of that
// with a small mini-language inside the {} placeholder itself: each format
// spec only ever affects the one value it's attached to.

#include <print>

int main() {

    // --- Basic printing ---
    // std::println already appends the newline for you - no std::endl needed.
    std::println("Hello");
    std::println("World");

    std::println("-------------");

    // --- Field width: {:N} pads a value to at least N characters ---
    std::println("");
    std::println("Unformatted expense list:");
    std::println("Coffee 4");
    std::println("Groceries 62");
    std::println("Parking 5");
    std::println("Internet 45");

    std::println("");
    std::println("Formatted with fixed-width columns:");
    std::println("{:<10}{:>6}", "Coffee", 4);
    std::println("{:<10}{:>6}", "Groceries", 62);
    std::println("{:<10}{:>6}", "Parking", 5);
    std::println("{:<10}{:>6}", "Internet", 45);
    // {:<10} = left-justified in a 10-character field.
    // {:>6}  = right-justified in a 6-character field.
    // Justification and width live together in the spec - no separate
    // manipulator call needed before each value like std::setw() required.

    // --- Fill characters: {:*<10} pads with * instead of spaces ---
    std::println("");
    std::println("Same table with a fill character:");
    std::println("{:*<10}{:*>6}", "Coffee", 4);
    std::println("{:*<10}{:*>6}", "Groceries", 62);
    std::println("{:*<10}{:*>6}", "Parking", 5);
    std::println("{:*<10}{:*>6}", "Internet", 45);

    // --- Number bases: {:x}, {:o}, {:b} - each spec is independent ---
    // Unlike std::hex/std::oct, using {:x} here doesn't affect any other
    // value printed elsewhere - no leftover stream state to reset.
    std::println("");
    int categoryFlags{717171};
    std::println("categoryFlags (decimal)     : {}", categoryFlags);
    std::println("categoryFlags (hexadecimal) : {:x}", categoryFlags);
    std::println("categoryFlags (octal)       : {:o}", categoryFlags);
    std::println("categoryFlags (binary)      : {:b}", categoryFlags);
    std::println("categoryFlags (hex, upper)  : {:#X}", categoryFlags); // {:#X} adds the 0X prefix and uppercases digits

    // --- Precision: {:.Nf} controls digits after the decimal point ---
    std::println("");
    double pi{3.1415926535897932384626433832795};
    std::println("pi (default)      : {}", pi);
    std::println("pi (precision 2)  : {:.2f}", pi);
    std::println("pi (precision 10) : {:.10f}", pi);

    // --- Fixed vs scientific notation ---
    double annualRevenue{2006.0};
    double roundingFeeFraction{1.34e-10};
    std::println("");
    std::println("annualRevenue (default)    : {}", annualRevenue);
    std::println("annualRevenue (fixed)      : {:f}", annualRevenue);
    std::println("annualRevenue (scientific) : {:e}", annualRevenue);
    std::println("roundingFeeFraction (scientific): {:e}", roundingFeeFraction);

    // --- Combining width, fill, sign, and precision in one spec ---
    // A currency-style amount: always show a sign, pad to 12 characters,
    // 2 decimal places - one spec string instead of four separate
    // manipulator calls (std::showpos, std::setw, std::setfill,
    // std::setprecision) that all had to be individually reset afterward.
    std::println("");
    double expenseAmount{45.5};
    double refundAmount{-12.3};
    std::println("{:+12.2f}", expenseAmount);
    std::println("{:+12.2f}", refundAmount);

    return 0;
}
