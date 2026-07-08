// The expense tracker (4.9ExpenseTrackerProject) already writes its ledger
// to disk at the end of every run:
//
//     std::ofstream ledgerOut(ledgerFileName);
//     ledgerOut << nextTransactionId << " " << totalSpent << "\n";
//
// That single std::ofstream line is this entire lecture - you've already
// used it. Here's what's actually happening, and the options around it.

#include <print>
#include <fstream>
#include <string>

int main() {

    const std::string fileName = "notes.txt";

    // Opening a std::ofstream creates the file if it doesn't exist, and by
    // default truncates (empties) it if it does - same as the expense
    // tracker overwriting expenses.txt with the latest totals every run.
    std::ofstream out(fileName);

    // if (out) checks the stream's failure state - the same idiom
    // 4.9ExpenseTrackerProject uses on its ifstream when loading.
    if (!out) {
        std::println("Could not open {} for writing.", fileName);
        return 1;
    }

    // Writing to a file stream uses the exact same << you've used with
    // std::cout all along - a std::ofstream is just a stream aimed at a
    // file instead of the console.
    out << "Lecture: Writing file streams\n";
    out << "Line " << 2 << '\n';
    out << "Line " << 3 << '\n';

    // Closing isn't strictly required here - out's destructor closes it
    // automatically when it goes out of scope - but calling it explicitly
    // guarantees the data is flushed to disk before the next block reads it.
    out.close();
    std::println("Wrote 3 lines to {}.", fileName);

    // std::ios::app opens for *appending* instead of truncating - each
    // write adds to the end rather than replacing what's there. Useful for
    // a running log, as opposed to the expense tracker's "rewrite the whole
    // ledger every time" approach.
    std::ofstream appender(fileName, std::ios::app);
    appender << "Appended line 4\n";
    appender.close();
    std::println("Appended a 4th line to {}.", fileName);

    return 0;
}
