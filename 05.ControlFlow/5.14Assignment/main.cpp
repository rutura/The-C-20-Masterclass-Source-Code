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
    {
        /*
        std::print("Enter a grade (0-100): ");
        int grade{};
        std::cin >> grade;

        if (grade >= 90) {
            std::println("Letter: A");
        }
        else if (grade >= 80) {
            std::println("Letter: B");
        }
        else if (grade >= 70) {
            std::println("Letter: C");
        }
        else if (grade >= 60) {
            std::println("Letter: D");
        }
        else {
            std::println("Letter: F");
        }

        // Ternary: the whole `grade >= 60 ? "pass" : "fail"` is one value,
        // passed straight to println - no if statement needed.
        std::println("{}", grade >= 60 ? "pass" : "fail");
        */

    }


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
    {
        /*
        std::print("How many scores? ");
        int n{};
        std::cin >> n;

        int total{};
        for (int i{ 0 }; i < n; ++i) {
            std::print("Score {}: ", i + 1);
            int score{};
            std::cin >> score;
            total += score;
        }

        if (n == 0) {
            std::println("no scores");           // guard: never divide by 0
        }
        else {
            // static_cast<double> on one operand forces real division,
            // so 265 / 3 is 88.33..., not the integer 88.
            double average{static_cast<double>( total) / n };
            std::println("total {}, average {:.2f}", total, average);
        }
        */

    }


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
    {
        int passing{ 0 };
        int failing{ 0 };

        std::print("Score (-1 to stop): ");
        int score{};
        std::cin >> score;

        while (score != -1) {

            //Ignore any score outside the range
            if (score < 0 || score > 100) {
                std::print("Score (-1 to stop): ");
                std::cin >> score;
                continue;
            }

            if (score >= 60) {
                ++passing;
            }
            else {
                ++failing;
            }
            std::print("Score (-1 to stop): ");
            std::cin >> score;
        }

        std::println("passing: {}, failing: {}", passing, failing);

    }


    /*
        Exercise 4 - Grade histogram with switch

        Read grades one at a time until the user enters -1 (sentinel),
        using a while loop primed with one read before the loop. For
        each grade, use a switch on grade / 10 to append a '*' to the
        right letter-grade bar (A: 90-100, B: 80s, C: 70s, D: 60s,
        F: below 60) - each bar is its own std::string. After input
        ends, print each letter followed by its bar.

        Sample output (user enters 95 88 82 71 60 55 91 -1):
            Enter a grade (-1 to stop): > 95
            Enter a grade (-1 to stop): > 88
            Enter a grade (-1 to stop): > 82
            Enter a grade (-1 to stop): > 71
            Enter a grade (-1 to stop): > 60
            Enter a grade (-1 to stop): > 55
            Enter a grade (-1 to stop): > 91
            Enter a grade (-1 to stop): > -1
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
        Exercise 6 - Palindrome check

        std::string supports a way to grab an element at a given index:

            - full[i]     - fast, no bounds checking. Passing an
                            out-of-range i is undefined behavior - it
                            will not stop you.
            - full.at(i)  - same result, but checks the index first and
                            throws an exception if it's out of range.
                            Slightly slower, but safer.

        A palindrome is a word that reads the same forwards and
        backwards. Examples:
            "racecar" -> palindrome (7 characters, odd length)
            "abba"    -> palindrome (4 characters, even length)
            "hello"   -> not a palindrome

        The idea: walk one index in from the front (i) and one in from
        the back (j) at the same time, comparing word[i] to word[j] as
        you go. If they ever differ, it's not a palindrome. If the
        indices meet or cross in the middle without a mismatch, it is.

        Odd length - "racecar" (7 characters), the indices meet at the
        middle character:

            r  a  c  e  c  a  r
            0  1  2  3  4  5  6
            ^                 ^
           i=0              j=6    word[0]=='r', word[6]=='r' -> match, move in

               ^           ^
              i=1         j=5      word[1]=='a', word[5]=='a' -> match, move in

                  ^     ^
                 i=2   j=4         word[2]=='c', word[4]=='c' -> match, move in

                     ^^
                    i=3==j=3       i meets j - middle reached, no mismatch found

        Even length - "abba" (4 characters), the indices cross without
        ever landing on the same character:

            a  b  b  a
            0  1  2  3
            ^        ^
           i=0      j=3     word[0]=='a', word[3]=='a' -> match, move in

               ^  ^
              i=1 j=2       word[1]=='b', word[2]=='b' -> match, move in

               ^^
              i=2 j=1       i has crossed j (i > j) - middle reached, no mismatch found

        Either way, the loop should stop as soon as i is no longer less
        than j - that condition works for both odd and even lengths.

        Your task: write a loop that checks whether a std::string is a
        palindrome, following the walk-through above. Track the result
        in a bool (true until you find a mismatch). Only one `word`
        variable should be active at a time - leave the other two
        commented out - so you write and test the loop just once. Try
        each of "racecar" (odd length), "abba" (even length), and
        "hello" (not a palindrome) by uncommenting one at a time,
        rebuilding, and rerunning.

        Sample output (with "racecar" active):
            "racecar" is a palindrome: true
    */
    std::println("\n--- Exercise 6: String report line ---");
    // TODO
    {
        // Try each word one at a time - comment out two, leave one
        // active, rebuild and rerun to see the loop handle each case.
        std::string word{"racecar"};    // odd length - has a middle character
        // std::string word{"abba"};    // even length - no middle character
        // std::string word{"hello"};   // not a palindrome

        bool is_palindrome{true};

        // TODO: YOUR LOOP GOES BELOW THIS LINE


        // TODO: YOUR LOOP GOES ABOVE THIS LINE

        std::println("\"{}\" is a palindrome: {}", word, is_palindrome);
    }

    return 0;
}