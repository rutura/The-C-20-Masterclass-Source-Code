// Chapter 5 capstone: a bill splitter and tip calculator.
//
// You've just eaten out with friends. This program takes the items on the
// bill, works out tax and tip, splits the total evenly, and warns anyone
// whose share blows past what they budgeted for the meal - putting every
// operator from this chapter to work on one practical problem.

#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

double promptItemPrice(const std::string& itemName) {
    std::print("Price of {}: ", itemName);
    double price{};
    std::cin >> price;
    std::cin.ignore();
    return price;
}

int main() {

    std::vector<std::string> itemNames;
    std::vector<double> itemPrices;

    // 5.4 Increment and Compound Assignment: itemCount ticks up by one per
    // item, and runningSubtotal accumulates with += instead of being
    // reassigned from scratch each time.
    int itemCount{};
    double runningSubtotal{};

    std::println("Let's split the bill. Enter each item, or a blank name to stop.\n");

    while (true) {
        std::print("Item name: ");
        std::string itemName;
        std::getline(std::cin, itemName);

        if (itemName.empty()) {
            break;
        }

        double price = promptItemPrice(itemName);

        itemNames.push_back(itemName);
        itemPrices.push_back(price);

        ++itemCount;
        runningSubtotal += price;
    }

    std::print("How many people are splitting the bill? ");
    int peopleSplitting{};
    std::cin >> peopleSplitting;
    std::cin.ignore();

    std::print("Tip percentage (e.g. 18): ");
    int tipPercent{};
    std::cin >> tipPercent;
    std::cin.ignore();

    std::print("Tax percentage (e.g. 8): ");
    int taxPercent{};
    std::cin >> taxPercent;
    std::cin.ignore();

    std::print("Each person's budget for this meal: ");
    double perPersonBudget{};
    std::cin >> perPersonBudget;
    std::cin.ignore();

    // 5.2 Basic Operations + 5.3 Precedence: tip and tax are each a
    // percentage *of the subtotal*, so the multiplication and division must
    // happen before adding them on - parentheses make that grouping explicit
    // rather than relying on precedence rules alone to be obvious to a reader.
    double tipAmount = (runningSubtotal * tipPercent) / 100;
    double taxAmount = (runningSubtotal * taxPercent) / 100;
    double grandTotal = runningSubtotal + tipAmount + taxAmount;

    // Splitting money evenly rarely comes out exact - integer division
    // between whole cents would silently drop the remainder, which is
    // exactly the kind of quiet bug chapter 5.8 warns about. Working in
    // double dollars and rounding for display, rather than truncating with
    // int, keeps the small remainder visible instead of losing it.
    double perPersonShare = grandTotal / peopleSplitting;

    // 5.9 Math Functions: round to a sensible amount for handing over
    // physical cash, and separately show what rounding up to the next whole
    // dollar would look like (handy if a card machine can't take cents).
    double perPersonShareRounded = std::round(perPersonShare * 100) / 100; // nearest cent
    double perPersonShareRoundedUpDollar = std::ceil(perPersonShare);      // next whole dollar

    // 5.5 Relational Operators + 5.6 Logical Operators: flag this split if
    // it blows the budget, and separately flag it if it's *close* to the
    // budget (within a dollar) even if technically under - two checks
    // combined with && / || rather than one big untestable condition.
    bool isOverBudget = perPersonShareRounded > perPersonBudget;
    bool isCloseToBudget = !isOverBudget && (perPersonBudget - perPersonShareRounded) <= 1.0;

    // 5.7 Output Formatting: a lined-up, receipt-style printout using
    // std::format's spec mini-language instead of stream manipulators.
    std::println("");
    std::println("---------------- Receipt ----------------");
    for (int i{}; i < itemCount; ++i) {
        std::println("{:<25}{:>10.2f}", itemNames[static_cast<size_t>(i)], itemPrices[static_cast<size_t>(i)]);
    }
    std::println("------------------------------------------");
    std::println("{:<25}{:>10.2f}", "Subtotal", runningSubtotal);
    std::println("{:<25}{:>10.2f}", "Tip (" + std::to_string(tipPercent) + "%)", tipAmount);
    std::println("{:<25}{:>10.2f}", "Tax (" + std::to_string(taxPercent) + "%)", taxAmount);
    std::println("{:<25}{:>10.2f}", "Grand total", grandTotal);
    std::println("------------------------------------------");
    std::println("{:<25}{:>10.2f}", "Per person (exact)", perPersonShare);
    std::println("{:<25}{:>10.2f}", "Per person (nearest cent)", perPersonShareRounded);
    std::println("{:<25}{:>10.2f}", "Per person (round up to $)", perPersonShareRoundedUpDollar);
    std::println("");
    std::println("Over budget ({:.2f})? {}", perPersonBudget, isOverBudget);
    std::println("Cutting it close (within $1)? {}", isCloseToBudget);

    // Save the receipt to a file, the same file-persistence idea chapter 3
    // ended on - so the group has a record after everyone's gone home.
    //
    // "receipt.txt" is a relative path, so it's created in whatever directory
    // you *ran the program from* - not necessarily next to main.cpp, and not
    // necessarily inside build/. Following this course's documented workflow
    // (running `./build/rooster` from this lecture folder) puts it right
    // here, next to main.cpp. If you instead cd into build/ first and run
    // `./rooster` from there, you'll find it inside build/ instead.
    std::ofstream receiptFile("receipt.txt");
    receiptFile << "Bill split among " << peopleSplitting << " people\n";
    receiptFile << "Subtotal: " << runningSubtotal << "\n";
    receiptFile << "Tip: " << tipAmount << "\n";
    receiptFile << "Tax: " << taxAmount << "\n";
    receiptFile << "Grand total: " << grandTotal << "\n";
    receiptFile << "Per person: " << perPersonShareRounded << "\n";
    std::println("\nSaved receipt.txt");

    return 0;
}
