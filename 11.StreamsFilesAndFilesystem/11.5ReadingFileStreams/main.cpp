// The expense tracker (4.9ExpenseTrackerProject) already reads its ledger
// back at the start of every run:
//
//     std::ifstream ledgerIn(ledgerFileName);
//     if (ledgerIn) {
//         if (ledgerIn >> savedNextId >> savedTotal) { ... }
//     }
//
// That's the >> style of reading - good for a handful of known, fixed-order
// values. This lecture covers that plus std::getline, which is what you
// reach for once a file has line-oriented or variable-length content.

#include <print>
#include <fstream>
#include <string>

int main() {

    const std::string fileName = "roster.txt";

    // Seed a file to read back, the same way a previous run of the expense
    // tracker would have already left expenses.txt on disk.
    {
        std::ofstream seed(fileName);
        seed << "3\n";           // how many students follow
        seed << "Alice 91\n";
        seed << "Bilal 78\n";
        seed << "Chen 88\n";
    }

    std::ifstream in(fileName);
    if (!in) {
        std::println("Could not open {} for reading.", fileName);
        return 1;
    }

    // --- >> extraction: good when you know exactly what's coming ---
    int studentCount{};
    in >> studentCount;
    std::println("studentCount : {}", studentCount);

    // >> stops at whitespace, so reading name then score works even though
    // they're on the same line - but it leaves the trailing '\n' unread,
    // same gotcha std::cin has (chapter 4's promptCategory calls
    // std::cin.ignore() for exactly this reason).
    in.ignore();

    std::println("");
    for (int i{}; i < studentCount; ++i) {
        std::string name;
        int score{};
        in >> name >> score;
        std::println("{} scored {}", name, score);
    }

    in.close();

    // --- std::getline: good for whole lines, unknown structure ---
    // Re-open and read the same file a different way - line by line,
    // without needing to know the record count up front.
    std::ifstream lineIn(fileName);
    std::println("");
    std::println("Same file, read line by line:");
    std::string line;
    while (std::getline(lineIn, line)) {
        std::println("  \"{}\"", line);
    }
    // getline returning false (the loop condition) is how you detect
    // end-of-file here - no separate eof() check needed.

    return 0;
}
