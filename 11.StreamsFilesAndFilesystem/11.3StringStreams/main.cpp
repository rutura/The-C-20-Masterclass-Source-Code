// A std::istringstream/std::ostringstream is the exact same >>/<< interface
// as std::cin/std::cout, just pointed at an in-memory std::string instead of
// the console. That's the whole idea: anything you already know how to do
// with cin/cout, you can do against a string you already have - no new
// syntax to learn, just a new "destination" for the stream.

#include <print>
#include <sstream>
#include <string>

int main() {

    // --- ostringstream: building a string piece by piece ---
    // Useful when a string needs to be assembled from several pieces
    // before it's used (e.g. a log line, a formatted record) rather than
    // printed immediately.
    std::ostringstream recordBuilder;
    recordBuilder << "Coffee" << ',' << 4.5 << ',' << "no receipt";
    std::string record = recordBuilder.str();
    std::println("Built record: {}", record);

    // --- istringstream: pulling a line apart into typed pieces ---
    // The expense tracker's own >> based prompts (chapter 4) already read
    // typed values one at a time from std::cin - an istringstream lets you
    // do that same >> extraction against a line you already have in memory,
    // e.g. after reading it whole with std::getline (which the next
    // lecture's file reading relies on).
    std::string line = "Groceries,62.75,yes";

    std::istringstream lineReader(line);
    std::string category;
    std::string amountText;
    std::string hasReceiptText;

    // getline with a custom delimiter (',' instead of the default '\n')
    // splits the string on commas, one field at a time.
    std::getline(lineReader, category, ',');
    std::getline(lineReader, amountText, ',');
    std::getline(lineReader, hasReceiptText, ',');

    std::println("");
    std::println("Parsed category    : {}", category);
    std::println("Parsed amountText  : {}", amountText);
    std::println("Parsed hasReceipt  : {}", hasReceiptText);

    // The extracted amountText is still just a string - convert it the same
    // way std::stod/std::stoi would for any other string (chapter 12).
    double amount = std::stod(amountText);
    std::println("Parsed amount as double : {:.2f}", amount);

    return 0;
}
