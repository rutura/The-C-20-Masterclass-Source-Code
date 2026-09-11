#include <print>
#include <regex>
#include <string>

int main() {

    // std::regex_match checks whether a whole string fits a pattern - the
    // pattern must account for every character, start to end.
    std::regex zipCode{R"(\d{5})"};   // exactly 5 digits
    std::println("regex_match against \\d{{5}}:");
    std::println("  \"02215\": {}", std::regex_match("02215", zipCode));
    std::println("  \"9876\":  {}", std::regex_match("9876", zipCode));

    // Character classes and quantifiers combine to describe a shape, not
    // literal characters: "a capital letter, then one or more lowercase".
    std::regex properName{"[A-Z][a-z]+"};
    std::println("\nregex_match against [A-Z][a-z]+:");
    std::println("  \"Wally\": {}", std::regex_match("Wally", properName));
    std::println("  \"E\":     {}", std::regex_match("E", properName));

    // {n,} means "n or more"; {n,m} means "between n and m inclusive".
    std::regex longNumber{R"(\d{3,})"};
    std::println("\nregex_match against \\d{{3,}}:");
    std::println("  \"123\":        {}", std::regex_match("123", longNumber));
    std::println("  \"12\":         {}", std::regex_match("12", longNumber));

    // regex_replace rewrites every match in a copy of the string - the
    // original is untouched.
    std::string data{"1\t2\t3\t4"};
    std::string csvLine{std::regex_replace(data, std::regex{"\t"}, ",")};
    std::println("\nafter replacing tabs with commas: {}", csvLine);

    // regex_search looks for a match ANYWHERE in the string, unlike
    // regex_match which demands the whole string fit. std::smatch captures
    // what was found.
    std::string contact{"Ada Lovelace, Home: 555-555-1234, Work: 555-555-4321"};
    std::regex phoneNumber{R"(\d{3}-\d{3}-\d{4})"};
    std::smatch match;

    std::println("\nfinding phone numbers in:\n{}", contact);
    while (std::regex_search(contact, match, phoneNumber)) {
        std::println("  {}", match.str());
        contact = match.suffix();   // continue searching after this match
    }

    return 0;
}
