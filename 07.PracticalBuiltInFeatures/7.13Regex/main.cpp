#include <print>
#include <regex>
#include <string>

int main() {

    // std::regex_match checks whether a whole string fits a pattern - the
    // pattern must account for every character, start to end.
    std::regex zip_code{R"(\d{5})"};   // exactly 5 digits
    std::println("regex_match against \\d{{5}}:");
    std::println("  \"02215\": {}", std::regex_match("02215", zip_code));
    std::println("  \"9876\":  {}", std::regex_match("9876", zip_code));

    // Character classes and quantifiers combine to describe a shape, not
    // literal characters: "a capital letter, then one or more lowercase".
    std::regex proper_name{"[A-Z][a-z]+"};
    std::println("\nregex_match against [A-Z][a-z]+:");
    std::println("  \"Wally\": {}", std::regex_match("Wally", proper_name));
    std::println("  \"E\":     {}", std::regex_match("E", proper_name));

    // {n,} means "n or more"; {n,m} means "between n and m inclusive".
    std::regex long_number{R"(\d{3,})"};
    std::println("\nregex_match against \\d{{3,}}:");
    std::println("  \"123\":        {}", std::regex_match("123", long_number));
    std::println("  \"12\":         {}", std::regex_match("12", long_number));

    // regex_replace rewrites every match in a copy of the string - the
    // original is untouched.
    std::string data{"1\t2\t3\t4"};
    std::string csv_line{std::regex_replace(data, std::regex{"\t"}, ",")};
    std::println("\nafter replacing tabs with commas: {}", csv_line);

    // regex_search looks for a match ANYWHERE in the string, unlike
    // regex_match which demands the whole string fit. std::smatch captures
    // what was found.
    std::string contact{"Ada Lovelace, Home: 555-555-1234, Work: 555-555-4321"};
    std::regex phone_number{R"(\d{3}-\d{3}-\d{4})"};
    std::smatch match;

    std::println("\nfinding phone numbers in:\n{}", contact);
    while (std::regex_search(contact, match, phone_number)) {
        std::println("  {}", match.str());
        contact = match.suffix();   // continue searching after this match
    }

    return 0;
}
