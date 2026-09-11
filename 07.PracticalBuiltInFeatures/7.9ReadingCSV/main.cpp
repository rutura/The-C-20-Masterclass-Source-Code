#include <print>
#include <string>
#include <vector>

#include "rapidcsv.h"

// PROJECT: reading a CSV file with a vendored library instead of hand-
// rolled stringstream splitting (7.6's istringstream works for one line,
// but real CSVs have quoting, headers, and missing-value rules that are
// easy to get subtly wrong by hand).

int main() {

    // rapidcsv::Document loads and parses the whole file on construction.
    // By default it expects a header row - "account,name,balance" here -
    // and uses those names to address columns.
    rapidcsv::Document document{"accounts.csv"};

    // GetColumn<T> reads one named column into a std::vector<T>, converting
    // each cell from text to T along the way.
    std::vector<int> accounts{document.GetColumn<int>("account")};
    std::vector<std::string> names{document.GetColumn<std::string>("name")};
    std::vector<double> balances{document.GetColumn<double>("balance")};

    std::println("{:<10}{:<10}{:>8}", "Account", "Name", "Balance");

    for (std::size_t i{0}; i < accounts.size(); ++i) {
        std::println("{:<10}{:<10}{:>8.2f}",
                      accounts.at(i), names.at(i), balances.at(i));
    }

    return 0;
}
