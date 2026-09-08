#include <iostream>
#include <print>
#include <string>

/*
    Chapter 5 assignment - solutions
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
    {
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
    {
        std::print("How many scores? ");
        int n{};
        std::cin >> n;

        int total{0};
        for (int i{0}; i < n; ++i) {
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
            double average{static_cast<double>(total) / n};
            std::println("total {}, average {:.2f}", total, average);
        }
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
    {
        int passing{0};
        int failing{0};

        std::print("Score (-1 to stop): ");
        int score{};
        std::cin >> score;                       // priming read

        while (score != -1) {
            if (score < 0 || score > 100) {
                std::print("Score (-1 to stop): ");
                std::cin >> score;
                continue;                        // out of range - don't tally
            }

            if (score >= 60) {
                ++passing;
            }
            else {
                ++failing;
            }

            std::print("Score (-1 to stop): ");
            std::cin >> score;                   // read next before re-testing
        }

        std::println("passing: {}, failing: {}", passing, failing);
    }


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
    {
        int aCount{0};
        int bCount{0};
        int cCount{0};
        int dCount{0};
        int fCount{0};

        std::print("Enter grades, end-of-file to finish: ");
        int grade{};
        while (std::cin >> grade) {
            switch (grade / 10) {
                case 10:                         // 100 lands here
                case 9:                          // 90-99 falls through to same body
                    ++aCount;
                    break;
                case 8:
                    ++bCount;
                    break;
                case 7:
                    ++cCount;
                    break;
                case 6:
                    ++dCount;
                    break;
                default:                         // anything below 60
                    ++fCount;
                    break;
            }
        }

        int counts[]{aCount, bCount, cCount, dCount, fCount};
        char letters[]{'A', 'B', 'C', 'D', 'F'};
        for (int i{0}; i < 5; ++i) {
            std::print("{}: ", letters[i]);
            for (int star{0}; star < counts[i]; ++star) {   // inner loop draws the bar
                std::print("*");
            }
            std::println("");
        }
    }


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
    {
        int grade{};
        do {                                     // body runs before the test,
            std::print("Enter a grade (0-100): ");// so the prompt always shows once
            std::cin >> grade;
        } while (grade < 0 || grade > 100);

        std::println("Accepted: {}", grade);
    }


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
    {
        std::string first{"Ada"};
        std::string last{"Lovelace"};

        std::string full{first + " " + last};    // "Ada" + " " + "Lovelace"
        std::println("full name: \"{}\", length {}", full, full.length());
        std::println("starts with \"Ada \" : {}", full.starts_with("Ada "));
        std::println("ends with \"ace\"    : {}", full.ends_with("ace"));
    }

    return 0;
}
