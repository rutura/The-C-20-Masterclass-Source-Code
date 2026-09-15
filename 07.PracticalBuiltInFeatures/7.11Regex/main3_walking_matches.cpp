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
    std::string shopping_list{"eggs milk  bread rice"};
    std::regex item{R"([\w]+)"};

    std::println("walking every item in \"{}\":", shopping_list);
    const std::sregex_iterator end;
    for (auto it = std::sregex_iterator{shopping_list.cbegin(), shopping_list.cend(), item};
        it != end; ++it) {
        std::println("  \"{}\"", (*it)[0].str());
    }

    // std::sregex_token_iterator does the same walk, but yields the
    // matched text directly through ->str() instead of a full match
    // object - simpler when you don't need the whole match_results.
    std::println("\nsame walk with a token iterator:");
    const std::sregex_token_iterator token_end;
    for (auto it = std::sregex_token_iterator{shopping_list.cbegin(), shopping_list.cend(), item};
        it != token_end; ++it) {
        std::println("  \"{}\"", it->str());
    }

    // Without telling it otherwise, a token iterator only ever yields
    // submatch 0 - the WHOLE match - even though this pattern has three
    // capture groups. The hour, minute, and second are matched, but
    // nothing pulls them out individually here.
    std::regex timestamp{R"(^(\d{1,2}):(\d{1,2}):(\d{1,2})$)"};
    std::string logged_at{"14:6:9"};

    std::println("\ndefault token iterator on a pattern WITH capture groups:");
    for (auto it = std::sregex_token_iterator{logged_at.cbegin(), logged_at.cend(), timestamp};
        it != token_end; ++it) {
        std::println("  \"{}\"", it->str());
    }

    // A token iterator can also target specific capture groups by index -
    // here, only groups 1 and 2 (hour, minute) of the same timestamp pattern.
    std::vector hour_and_minute{1, 2};

    std::println("\nhour and minute only, from \"{}\":", logged_at);
    for (auto it = std::sregex_token_iterator{logged_at.cbegin(), logged_at.cend(), timestamp, hour_and_minute};
        it != token_end; ++it) {
        std::println("  \"{}\"", it->str());
    }

    // Passing -1 instead of a capture-group index flips the meaning to
    // "everything that does NOT match" - splitting the string on the
    // pattern, like a delimiter-based tokenizer.
    std::regex delimiter{R"(\s*[,;]\s*)"};
    std::string tags{"backend,  urgent;needs-review"};

    std::vector<std::string> tokens{
        std::sregex_token_iterator{tags.cbegin(), tags.cend(), delimiter, -1},
        std::sregex_token_iterator{}};

    std::println("\nsplitting \"{}\" on ',' and ';':", tags);
    for (const auto& token : tokens) {
        std::println("  \"{}\"", token);
    }

    return 0;
}
