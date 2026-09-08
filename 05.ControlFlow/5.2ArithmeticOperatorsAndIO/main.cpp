#include <iostream>
#include <print>

int main() {

    // Read two monthly salaries from the user. 
    std::print("Enter two monthly salaries, separated by a space: ");
    int salary1{};
    int salary2{};
    std::cin >> salary1 >> salary2;

    // --- The arithmetic operators ---
    std::println("combined monthly : {}", salary1 + salary2);
    std::println("gap between them  : {}", salary1 - salary2);
    std::println("salary1 over a year : {}", salary1 * 12);

    // Integer / integer throws away the fractional part. If the two
    // salaries add up to an odd number, the average comes back rounded
    // down - e.g. 3500 + 4000 = 7500, and 7500 / 2 is 3750, but
    // 3500 + 4001 = 7501, and 7501 / 2 is still 3750, not 3750.5.
    std::println("average salary (int division)  : {}", (salary1 + salary2) / 2);

    // Make one operand a double and the division keeps the fraction.
    std::println("average salary (real division) : {}", (salary1 + salary2) / 2.0);

    // Modulus gives the remainder: split the combined pay into whole
    // 100s and see what's left over that doesn't make a full 100.
    std::println("combined pay, leftover under 100 : {}", (salary1 + salary2) % 100);

    // --- Precedence and associativity ---
    // * binds tighter than +, so this is salary1 + (salary2 * 12):
    // one month of the first salary plus a full year of the second.
    int mixed_total{salary1 + salary2 * 12};
    std::println("salary1 + salary2 * 12 : {}", mixed_total);

    // Parentheses override precedence when you want the addition first:
    // add both monthly salaries, then multiply by 12 for the yearly total.
    int household_year{(salary1 + salary2) * 12};
    std::println("(salary1 + salary2) * 12 : {}", household_year);

    // --- Compound assignment ---
    // pot += x is shorthand for pot = pot + x. The two friends pool
    // their pay, then take some back out for shared rent.
    int pot{salary1};
    pot += salary2;   // pool the second salary too
    pot -= 1200;      // shared rent comes out of the pot
    std::println("pot after += , -= : {}", pot);

    return 0;
}
