#include <print>
#include <regex>
#include <string>

int main() {

    // regex_search looks for a match ANYWHERE in the string, unlike
    // regex_match which demands the whole string fit.
    std::string line{"int total{0};   // running total of all sales"};
    std::regex comment{R"(//\s*(.+)$)"};

    if (std::smatch m; std::regex_search(line, m, comment)) {
        std::println("found comment: '{}'", m[1].str());
    } else {
        std::println("no comment found");
    }

    // A single regex_search only ever finds the FIRST match. To find every
    // match in a string, search, record what you found, then keep
    // searching the leftover text - match.suffix() is everything AFTER
    // the match just found.
    std::string contact{"Ada Lovelace, Home: 555-555-1234, Work: 555-555-4321"};
    std::regex phone_number{R"(\d{3}-\d{3}-\d{4})"};
    std::smatch match;

    std::println("\nfinding phone numbers in:\n{}", contact);
    while (std::regex_search(contact, match, phone_number)) {
        std::println("  {}", match.str());
        contact = match.suffix();   // shrink the search to what's left
    }

    return 0;
}
