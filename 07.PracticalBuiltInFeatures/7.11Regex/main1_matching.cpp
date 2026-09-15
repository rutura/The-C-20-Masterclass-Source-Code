#include <print>
#include <regex>
#include <string>

int main() {

    // A regex describes the SHAPE of text, not literal characters:
    // "a capital letter, then one or more lowercase letters".
    std::regex city_name{"[A-Z][a-z]+"};
    std::println("regex_match against [A-Z][a-z]+:");
    std::println("  \"Nairobi\": {}", std::regex_match("Nairobi", city_name));
    std::println("  \"K\":       {}", std::regex_match("K", city_name));

    // regex_match demands the WHOLE string fit the pattern, start to end -
    // a trailing character the pattern doesn't account for is enough to fail.
    std::regex invoice_code{R"(\d{5})"};   // exactly 5 digits
    std::println("\nregex_match against \\d{{5}}:");
    std::println("  \"48213\":  {}", std::regex_match("48213", invoice_code));
    std::println("  \"48213-1\":{}", std::regex_match("48213-1", invoice_code));

    // Parentheses mark a capture group. Wrapping the year/month/day parts
    // of a date pattern in () lets us pull each one back out after a match.
    std::regex ship_date{R"((\d{4})/(\d{1,2})/(\d{1,2}))"};
    std::string input{"2025/3/9"};

    // smatch receives the results of the match: [0] is the whole match,
    // [1], [2], [3] are the three capture groups, in the order they open.
    if (std::smatch m; std::regex_match(input, m, ship_date)) {
        int year{std::stoi(m[1])};
        int month{std::stoi(m[2])};
        int day{std::stoi(m[3])};
        std::println("\nmatched \"{}\": year={}, month={}, day={}",
            input, year, month, day);
    }

    return 0;
}
