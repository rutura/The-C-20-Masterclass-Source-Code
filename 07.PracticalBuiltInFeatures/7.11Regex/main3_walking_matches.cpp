#include <print>
#include <regex>
#include <string>
#include <vector>

int main() {

    // The suffix()-shrinking loop from the previous file works, but it
    // rebuilds the string on every pass. std::sregex_iterator walks every
    // match directly, the same begin/end/++ shape a range-based for loop
    // has been driving for you since std::array: sregex_iterator{} (no
    // arguments) marks "one past the last match", the same role end()
    // plays for a container.
    std::string sentence{"This is  a test string."};
    std::regex word{R"([\w]+)"};

    std::println("walking every word in \"{}\":", sentence);
    const std::sregex_iterator end;
    for (auto it = std::sregex_iterator{sentence.cbegin(), sentence.cend(), word};
        it != end; ++it) {
        std::println("  \"{}\"", (*it)[0].str());
    }

    // std::sregex_token_iterator does the same walk, but yields the
    // matched text directly through ->str() instead of a full match
    // object - simpler when you don't need the whole match_results.
    std::println("\nsame walk with a token iterator:");
    const std::sregex_token_iterator token_end;
    for (auto it = std::sregex_token_iterator{sentence.cbegin(), sentence.cend(), word};
        it != token_end; ++it) {
        std::println("  \"{}\"", it->str());
    }

    // Without telling it otherwise, a token iterator only ever yields
    // submatch 0 - the WHOLE match - even though this pattern has three
    // capture groups. The year, month, and day are matched, but nothing
    // pulls them out individually here.
    std::regex date{R"(^(\d{4})/(\d{1,2})/(\d{1,2})$)"};
    std::string when{"2024/6/22"};

    std::println("\ndefault token iterator on a pattern WITH capture groups:");
    for (auto it = std::sregex_token_iterator{when.cbegin(), when.cend(), date};
        it != token_end; ++it) {
        std::println("  \"{}\"", it->str());
    }

    // A token iterator can also target specific capture groups by index -
    // here, only groups 2 and 3 (month, day) of the same date pattern.
    std::vector month_and_day{2, 3};

    std::println("\nmonth and day only, from \"{}\":", when);
    for (auto it = std::sregex_token_iterator{when.cbegin(), when.cend(), date, month_and_day};
        it != token_end; ++it) {
        std::println("  \"{}\"", it->str());
    }

    // Passing -1 instead of a capture-group index flips the meaning to
    // "everything that does NOT match" - splitting the string on the
    // pattern, like a delimiter-based tokenizer.
    std::regex delimiter{R"(\s*[,;]\s*)"};
    std::string csv{"This is,  a;test string."};

    std::vector<std::string> tokens{
        std::sregex_token_iterator{csv.cbegin(), csv.cend(), delimiter, -1},
        std::sregex_token_iterator{}};

    std::println("\nsplitting \"{}\" on ',' and ';':", csv);
    for (const auto& token : tokens) {
        std::println("  \"{}\"", token);
    }

    return 0;
}
