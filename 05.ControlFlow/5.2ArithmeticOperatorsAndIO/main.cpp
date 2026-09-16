#include <iostream>
#include <print>


int main(){
    // Read two monthly salaries from the user. 
    std::println("Enter two monthly salaries separated by a space: ");
    int salary1{};
    int salary2{};
    std::cin >> salary1 >> salary2;

    // --- The arithmetic operators ---
    std::println("Combined monthly: {}", salary1 + salary2);
    std::println("Gap between them: {}", salary1 - salary2);
    std::println("Salary over the year: {}", salary1 * 12);

    // Integer / integer throws away the fractional part. If the two
    // salaries add up to an odd number, the average comes back rounded
    // down - e.g. 3500 + 4000 = 7500, and 7500 / 2 is 3750, but
    // 3500 + 4001 = 7501, and 7501 / 2 is still 3750, not 3750.5.
    std::println("Average salary (int division): {}", (salary1 + salary2) / 2);

    // Make one operand a double and the division keeps the fraction.
    std::println("average salary (real division) : {}", (salary1 + salary2) / 2.0);


    // Modulus gives the remainder: split the combined pay into whole
    // 100s and see what's left over that doesn't make a full 100.
    std::println("combined pay, leftover under 100 : {}", (salary1 + salary2) % 100);

    // --- Precedence and associativity ---
    // * binds tighter than +, so this is salary1 + (salary2 * 12):
    // one month of the first salary plus a full year of the second.
    int mixed_total{ (salary1 + salary2) * 12 };
    std::println("salary1 + salary2 * 12 : {}", mixed_total);

    // --- Compound assignment ---
    // pot += x is shorthand for pot = pot + x. The two friends pool
    // their pay, then take some back out for shared rent.
    int pot{ salary1 };
    pot += salary2;
    pot -= 1200;
    std::println("pot after += , -= : {}", pot);



}