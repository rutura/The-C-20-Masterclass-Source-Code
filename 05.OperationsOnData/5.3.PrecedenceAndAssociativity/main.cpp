#include <print>

int main() {

    int lunch{6};
    int coffee{3};
    int snack{8};
    int tip{9};
    int discount{3};
    int serviceFee{2};
    int giftCredit{5};

    // Without parentheses, C++ follows the same order-of-operations rules as
    // arithmetic on paper: * and / bind tighter than + and -, so they run
    // first regardless of how the expression reads left to right.
    int total = lunch + coffee * snack - tip / discount - serviceFee + giftCredit;
    // reads as: lunch + (coffee * snack) - (tip / discount) - serviceFee + giftCredit
    //         =    6   +      24        -       3          -     2     +    5
    std::println("total (no parens)  : {}", total);

    total = lunch / coffee * snack + tip - discount + serviceFee;
    // reads as: ((lunch / coffee) * snack) + tip - discount + serviceFee
    //         =           16            +  9  -  3  +  2
    std::println("total (no parens 2): {}", total);

    // Parentheses override precedence, forcing an operation to happen first -
    // useful when you actually mean "add these two costs together, then
    // multiply", not "multiply, then add".
    total = (lunch + coffee) * snack - tip / discount - serviceFee + giftCredit;
    // reads as: ((lunch + coffee) * snack) - (tip / discount) - serviceFee + giftCredit
    //         =         72              -        3            -     2     +    5
    std::println("total (with parens): {}", total);

    return 0;
}
