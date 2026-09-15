#include <print>
#include <regex>
#include <string>

int main() {

    // regex_search looks for a match ANYWHERE in the string, unlike
    // regex_match which demands the whole string fit.
    std::regex fun{"fun"};
    std::println("regex_match(\"Debugging is fun\", fun): {}",
        std::regex_match("Debugging is fun", fun));
    std::println("regex_search(\"Debugging is fun\", fun): {}",
        std::regex_search("Debugging is fun", fun));

    // A single regex_search only ever finds the FIRST match. To find every
    // match in a string, search, record what you found, then keep
    // searching the leftover text - match.suffix() is everything AFTER
    // the match just found.
    std::string ticket{"Grace Hopper, Order: TCK-9001, Follow-up: TCK-9042"};
    std::regex ticket_id{R"(TCK-\d{4})"};
    std::smatch match;

    std::println("\nfinding ticket IDs in:\n{}", ticket);
    while (std::regex_search(ticket, match, ticket_id)) {
        std::println("  {}", match.str());
        ticket = match.suffix();   // shrink the search to what's left
    }

    return 0;
}
