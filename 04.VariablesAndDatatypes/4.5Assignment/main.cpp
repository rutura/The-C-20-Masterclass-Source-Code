#include <iostream>
#include <print>
#include <string>

/*
    Chapter 4 assignment
*/

// Exercise 4: a function goes here, above main, so main can call it.
// See the "Exercise 4" comment below for what to write.

int main() {

    /*
        Exercise 1 - Personal profile card

        Declare variables for a name, age, height (in meters, as a
        double), and whether the person is a student (bool). Print all
        four in a single formatted sentence using std::println
        or std::cout (if you don't have access to std::println).
    */
    std::println("--- Exercise 1: Personal profile card ---");
    // TODO: declare name/age/height/is_student and print them here.


    /*
        Exercise 2 - Receipt printer

        Declare six variables as literals in code, exactly as follows:
            coffee_price  (double)  4.50      coffee_qty  (int)  2
            muffin_price  (double)  3.25      muffin_qty  (int)  1
            juice_price   (double)  2.75      juice_qty   (int)  3

        Compute a line total for each item (price * quantity) and a
        grand total (the sum of all three line totals).

        Print exactly four lines, in this order, with a $ before each
        amount and amounts printed to 2 decimal places (use
        std::format's {:.2f} spec, e.g. std::println("{:.2f}", 9.0)
        prints "9.00"):
            Coffee 2x : $9.00
            Muffin 1x : $3.25
            Juice  3x : $8.25
            Grand total  : $20.50
        The label column (everything before the " : ") must line up
        exactly as shown above - pad "Juice " with one trailing space so
        it's the same width as "Coffee" and "Muffin".
    */
    std::println("\n--- Exercise 2: Receipt printer ---");
    // TODO: declare the six variables above, compute the four totals,
    // and print the four-line receipt exactly as specified above.


    /*
        Exercise 3 - Base converter tool

        Prompt the user (std::cin) for a decimal integer, then print it
        back out in octal, hex, and binary using std::println's format
        spec - the same {:#o}/{:#x}/{:#b} syntax from 4.2NumberSystems,
        but on a value read from input instead of a hardcoded literal.
    */
    std::println("\n--- Exercise 3: Base converter tool ---");
    // TODO: read an int from std::cin and print it in octal/hex/binary.


    /*
        Exercise 4 - Unit price calculator (function)

        Write a function double unit_price(double total_cost, int quantity)
        above main that returns cost-per-item. Define it near the top of
        this file (see the placeholder above main), then call it here
        with at least two different sets of literal inputs and print the
        results.
    */
    std::println("\n--- Exercise 4: Unit price calculator ---");
    // TODO: call your unit_price(...) function with a couple of
    // different inputs and print the results here.


    /*
        Exercise 5 - auto detective

        Before compiling, predict the deduced type for each auto
        declaration below (an int literal, a literal with a u/ll/f
        suffix, a bare string literal, an "s"-suffixed string literal,
        and an expression mixing int and double). Then use sizeof and
        std::println to check your predictions - a bare string literal
        deduces to const char*, not std::string, unless you use the "s"
        suffix (see 4.4Auto for the full explanation).
    */
    std::println("\n--- Exercise 5: auto detective ---");
    // TODO: declare each of the auto variables described above and
    // print their sizeof() to check your predictions.


    /*
        Exercise 6 - Change-maker (chapter capstone)

        Read a bill total and an amount paid from std::cin (both
        double). Compute the change owed, convert it to a whole-cents
        long long (money math should use integer cents, not floating
        point, to avoid rounding errors - this is the same reasoning
        4.3DataTypes used long long for yearly_total_cents), then split
        that into whole dollars and remaining cents using integer
        division and modulo. Print "you get $X and Y cents back".
        Optional: wrap the cents-to-dollars-and-cents split in its own
        function, the same way Exercise 4 does.
    */
    std::println("\n--- Exercise 6: Change-maker ---");
    // TODO: read bill total and amount paid, compute change in cents,
    // split into dollars/cents, and print the result here.

    return 0;
}