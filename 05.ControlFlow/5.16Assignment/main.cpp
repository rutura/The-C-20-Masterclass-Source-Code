#include <iostream>
#include <print>
#include <string>

/*
    Chapter 5 assignment - Control Flow

    Every exercise builds on the class results analyzer from the
    chapter. Use std::print / std::println (or std::cout if your
    compiler lacks <print>). Brace-initialize every variable.
*/

int main() {

    /*
        Exercise 1 - Letter grade classifier

        Read one integer grade (0-100) from std::cin. Print its letter
        using an else-if ladder:
            >= 90 -> A , >= 80 -> B , >= 70 -> C , >= 60 -> D , else F
        Then print, on a second line, "pass" if the grade is >= 60 and
        "fail" otherwise - this time using the ternary operator, not an
        if statement.
    */
    std::println("--- Exercise 1: Letter grade classifier ---");
    // TODO


    /*
        Exercise 2 - Average of a fixed number of scores

        Ask the user how many scores they will enter (call it n). Then
        loop exactly n times with a counter-controlled for loop, reading
        one score each pass and adding it to a running total. After the
        loop, print the total and the average to 2 decimal places
        (average = total / n as a real division, not integer division).
        If n is 0, print "no scores" instead of dividing.
    */
    std::println("\n--- Exercise 2: Average of n scores ---");
    // TODO


    /*
        Exercise 3 - Sentinel-controlled tally

        Read scores from std::cin until the user enters -1. Count how
        many were passing (>= 60) and how many were failing, using a
        while loop primed with one read before the loop. Print both
        counts. Use `continue` to skip any score entered outside the
        0-100 range without counting it.
    */
    std::println("\n--- Exercise 3: Sentinel-controlled tally ---");
    // TODO


    /*
        Exercise 4 - Grade histogram with switch

        Read grades until end-of-file (while (std::cin >> grade)). For
        each one, use a switch on grade / 10 to increment the right
        letter-grade counter (A: 90-100, B: 80s, C: 70s, D: 60s,
        F: below). After input ends, print each letter followed by a bar
        of that many '*' characters, e.g.  A: ***  .
        Build each bar with an inner loop.
    */
    std::println("\n--- Exercise 4: Grade histogram ---");
    // TODO


    /*
        Exercise 5 - Retry prompt with do...while

        Using a do...while loop, keep prompting "Enter a grade (0-100): "
        until the user enters a value actually in range. Then print the
        accepted value. The prompt must appear at least once.
    */
    std::println("\n--- Exercise 5: Retry prompt ---");
    // TODO


    /*
        Exercise 6 - String report line

        Given std::string first{"Ada"}; and std::string last{"Lovelace"};
        build a full name by concatenation, print it and its length,
        then report whether the full name starts with "Ada " and whether
        it ends with "ace" using starts_with / ends_with.
    */
    std::println("\n--- Exercise 6: String report line ---");
    // TODO

    return 0;
}
