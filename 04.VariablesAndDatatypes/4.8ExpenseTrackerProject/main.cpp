// Chapter 4 capstone project: a small personal expense tracker.
//
// This isn't a new concept - it's a chance to put every type decision from
// 4.2 through 4.7 to work on something you might actually use: logging what
// you spent today, category by category, and keeping a running ledger on disk
// between runs (the same file-persistence idea chapter 3 ended on).

#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <fstream>

// struct isn't introduced yet, so each expense is tracked as several parallel
// vectors instead - one entry per expense, at the same index in every vector.
// (We'll replace this with a proper struct once a later chapter introduces them.)

char promptCategory() {
    std::println("Category codes: F = Food, T = Transport, E = Entertainment, O = Other");
    std::print("Category: ");
    char category{};
    std::cin >> category;
    std::cin.ignore(); // discard the leftover newline, same trick as chapter 3
    return category;
}

double promptAmount() {
    std::print("Amount spent: ");
    double amount{};
    std::cin >> amount;
    std::cin.ignore();
    return amount;
}

bool promptHasReceipt() {
    std::print("Do you have a receipt? (y/n): ");
    char answer{};
    std::cin >> answer;
    std::cin.ignore();
    return answer == 'y' || answer == 'Y';
}

int main() {

    std::vector<char> categories;
    std::vector<double> amounts;
    std::vector<bool> hasReceipts;

    // A running total needs to hold fractional currency, so double - not int.
    double totalSpent{};

    // A bitmask of which categories were used this session: bit 0 = Food,
    // bit 1 = Transport, bit 2 = Entertainment, bit 3 = Other. Small, fixed
    // set of yes/no flags - exactly what packed bits are good for (4.2).
    int categoriesUsedMask{0b0000};

    // Session-long counters. A short is plenty for "expenses logged today".
    short expenseCount{};

    // A transaction id that keeps climbing across every run of this program
    // (loaded back from disk below) needs more headroom than a short or int
    // would give it over months of use - long long, same reasoning as 4.3.
    long long nextTransactionId{1000};

    // A relative filename like this is created in whatever directory you
    // *ran the program from*, not necessarily next to main.cpp or inside
    // build/. Following this course's documented workflow (running
    // `./build/rooster` from this lecture folder) puts it right here, next
    // to main.cpp; cd-ing into build/ first and running `./rooster` from
    // there would put it inside build/ instead.
    const std::string ledgerFileName = "expenses.txt";

    // --- Load the existing ledger, if one exists from a previous run ---
    std::ifstream ledgerIn(ledgerFileName);
    if (ledgerIn) {
        long long savedNextId{};
        double savedTotal{};
        if (ledgerIn >> savedNextId >> savedTotal) {
            nextTransactionId = savedNextId;
            totalSpent = savedTotal;
            std::println("Loaded existing ledger: {} spent so far, next id is {}.",
                          totalSpent, nextTransactionId);
        }
    }

    std::println("\nLet's log today's expenses.\n");

    while (true) {
        char category = promptCategory();
        double amount = promptAmount();
        bool receipted = promptHasReceipt();

        categories.push_back(category);
        amounts.push_back(amount);
        hasReceipts.push_back(receipted);

        totalSpent += amount;
        ++expenseCount;

        long long thisTransactionId = nextTransactionId;
        ++nextTransactionId;

        // Fold this category into the bitmask using its matching bit.
        switch (category) {
            case 'F': categoriesUsedMask |= 0b0001; break;
            case 'T': categoriesUsedMask |= 0b0010; break;
            case 'E': categoriesUsedMask |= 0b0100; break;
            case 'O': categoriesUsedMask |= 0b1000; break;
            default: break;
        }

        std::println("Logged expense #{}: {} = {:.2f} (receipt: {})\n",
                     thisTransactionId, category, amount, receipted);

        std::print("Add another expense? (y/n): ");
        char again{};
        std::cin >> again;
        std::cin.ignore();
        if (again != 'y' && again != 'Y') {
            break;
        }
    }

    // --- Session summary ---
    // budgetLimit is deliberately auto - the compiler deduces double from the
    // literal, so it lines up with totalSpent without us spelling it out twice.
    auto budgetLimit = 100.0;
    bool isOverBudget = totalSpent > budgetLimit;

    std::println("--------------------------------------");
    std::println("Expenses logged this session: {}", expenseCount);
    std::println("Total spent                 : {:.2f}", totalSpent);
    std::println("Over budget ({:.2f})?         : {}", budgetLimit, isOverBudget);
    std::println("Categories used (binary)     : {:#06b}", categoriesUsedMask);
    std::println("Categories used (hex)        : {:#x}", categoriesUsedMask);

    // --- A narrowing pitfall worth seeing once, on purpose ---
    // If you carelessly store the running total in an int "because it's just
    // a total", every cent gets silently dropped. Braced initialization would
    // have refused to compile this; a plain assignment lets it through.
    int badTotal = totalSpent; // narrowing: fractional cents are silently lost
    std::println("\n(Demonstration only) totalSpent as int: {} <- notice the lost cents!", badTotal);

    // --- Save the ledger back to disk for next time ---
    std::ofstream ledgerOut(ledgerFileName);
    ledgerOut << nextTransactionId << " " << totalSpent << "\n";
    std::println("\nSaved ledger to {} - next id will start at {}.", ledgerFileName, nextTransactionId);

    return 0;
}
