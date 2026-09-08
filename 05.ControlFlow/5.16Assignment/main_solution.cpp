#include <iostream>
#include <print>
#include <string>

/*
    Chapter 5 assignment - solutions

    Solves every exercise from main.cpp using only the control-flow
    tools introduced in this chapter.
*/

int main() {

    // --- Exercise 1: Letter grade classifier ---
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

        std::println("{}", grade >= 60 ? "pass" : "fail");
    }


    // --- Exercise 2: Average of n scores ---
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
            std::println("no scores");
        }
        else {
            double average{static_cast<double>(total) / n};
            std::println("total {}, average {:.2f}", total, average);
        }
    }


    // --- Exercise 3: Sentinel-controlled tally ---
    std::println("\n--- Exercise 3: Sentinel-controlled tally ---");
    {
        int passing{0};
        int failing{0};

        std::print("Score (-1 to stop): ");
        int score{};
        std::cin >> score;

        while (score != -1) {
            if (score < 0 || score > 100) {
                std::print("Score (-1 to stop): ");
                std::cin >> score;
                continue;               // out of range - don't count it
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


    // --- Exercise 4: Grade histogram ---
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
                case 10:
                case 9:
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
                default:
                    ++fCount;
                    break;
            }
        }

        int counts[]{aCount, bCount, cCount, dCount, fCount};
        char letters[]{'A', 'B', 'C', 'D', 'F'};
        for (int i{0}; i < 5; ++i) {
            std::print("{}: ", letters[i]);
            for (int star{0}; star < counts[i]; ++star) {
                std::print("*");
            }
            std::println("");
        }
    }


    // --- Exercise 5: Retry prompt ---
    std::println("\n--- Exercise 5: Retry prompt ---");
    {
        int grade{};
        do {
            std::print("Enter a grade (0-100): ");
            std::cin >> grade;
        } while (grade < 0 || grade > 100);

        std::println("Accepted: {}", grade);
    }


    // --- Exercise 6: String report line ---
    std::println("\n--- Exercise 6: String report line ---");
    {
        std::string first{"Ada"};
        std::string last{"Lovelace"};

        std::string full{first + " " + last};
        std::println("full name: \"{}\", length {}", full, full.length());
        std::println("starts with \"Ada \" : {}", full.starts_with("Ada "));
        std::println("ends with \"ace\"    : {}", full.ends_with("ace"));
    }

    return 0;
}
