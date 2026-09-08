#include <iostream>
#include <print>
#include <string>

/*
    Chapter 5 assignment - Control Flow

    Six exercises, each exercising the control-flow tools from this
    chapter. Use std::print / std::println (or std::cout if your compiler
    lacks <print>). Brace-initialize every variable.

    In the sample outputs below, text after a ">" on the same line is
    what the user typed.
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

        Sample output (user enters 73):
            Enter a grade (0-100): > 73
            Letter: C
            pass

        Sample output (user enters 41):
            Enter a grade (0-100): > 41
            Letter: F
            fail
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

        Sample output (user enters 3, then 80 90 95):
            How many scores? > 3
            Score 1: > 80
            Score 2: > 90
            Score 3: > 95
            total 265, average 88.33

        Sample output (user enters 0):
            How many scores? > 0
            no scores
    */
    std::println("\n--- Exercise 2: Average of n scores ---");
    // TODO


    /*
        Exercise 3 - Sentinel-controlled tally

        Read scores from std::cin until the user enters -1. Count how
        many were passing (>= 60) and how many were failing, using a
        while loop primed with one read before the loop. Print both
        counts. Use `continue` to skip any score entered outside the
        0-100 range without counting it (do not print an error for it,
        just don't tally it).

        Sample output (user enters 75 40 200 60 -1):
            Score (-1 to stop): > 75
            Score (-1 to stop): > 40
            Score (-1 to stop): > 200
            Score (-1 to stop): > 60
            Score (-1 to stop): > -1
            passing: 2, failing: 1

        (200 is out of range, so it is skipped and not counted.)
    */
    std::println("\n--- Exercise 3: Sentinel-controlled tally ---");
    // TODO


    /*
        Exercise 4 - Grade histogram with switch

        Read grades until end-of-file (while (std::cin >> grade)). For
        each one, use a switch on grade / 10 to increment the right
        letter-grade counter (A: 90-100, B: 80s, C: 70s, D: 60s,
        F: below 60). After input ends, print each letter followed by a
        bar of that many '*' characters. Build each bar with an inner
        loop.

        Sample output (user enters 95 88 82 71 60 55 91, then Ctrl+Z):
            Enter grades, end-of-file to finish: > 95 88 82 71 60 55 91
            A: **
            B: **
            C: *
            D: *
            F: *
    */
    std::println("\n--- Exercise 4: Grade histogram ---");
    // TODO


    /*
        Exercise 5 - Retry prompt with do...while

        Using a do...while loop, keep prompting "Enter a grade (0-100): "
        until the user enters a value actually in range (0 to 100). Then
        print the accepted value. The prompt must appear at least once.

        Sample output (user enters -5, then 130, then 72):
            Enter a grade (0-100): > -5
            Enter a grade (0-100): > 130
            Enter a grade (0-100): > 72
            Accepted: 72
    */
    std::println("\n--- Exercise 5: Retry prompt ---");
    // TODO


    /*
        Exercise 6 - String report line

        Given std::string first{"Ada"}; and std::string last{"Lovelace"};
        build a full name by concatenation (with a space between), print
        it and its length, then report whether the full name starts with
        "Ada " and whether it ends with "ace" using starts_with /
        ends_with.

        Sample output (no input needed):
            full name: "Ada Lovelace", length 12
            starts with "Ada " : true
            ends with "ace"    : true
    */
    std::println("\n--- Exercise 6: String report line ---");
    // TODO

    return 0;
}
