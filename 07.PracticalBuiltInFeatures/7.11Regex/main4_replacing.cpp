#include <print>
#include <regex>
#include <string>

int main() {

    // regex_replace rewrites every match in a copy of the string - the
    // original is untouched.
    std::string data{"apple|3|0.99"};
    std::println("Before replacing pipes with commas: {}", data);
    std::string csv_line{std::regex_replace(data, std::regex{R"(\|)"}, ",")};
    std::println("after replacing pipes with commas: {}", csv_line);
    std::println("Data is unchanged after replacement: {}", data);

    // The replacement string can reference capture groups with $1, $2, ...
    // Here group 1 is the title text, group 2 is the summary text.
    // Harvest the data out of the markup using the regex's capture groups
    // and reassemble it into the replacement string.
    std::string article{"<article><title>Launch Day</title><summary>It shipped</summary></article>"};
    std::regex markup{"<title>(.*)</title><summary>(.*)</summary>"};
    std::string replacement{"TITLE=$1 and SUMMARY=$2"};

    std::string default_result{std::regex_replace(article, markup, replacement)};
    std::println("\noriginal:        '{}'", article);
    std::println("default replace: '{}'", default_result);

    // format_no_copy drops everything that did NOT match instead of
    // copying it through untouched - only the replaced text survives.
    std::string no_copy_result{std::regex_replace(article, markup, replacement,
        std::regex_constants::format_no_copy)};
    std::println("format_no_copy:  '{}'", no_copy_result);

    // Combining a capture group with format_no_copy turns replace into a
    // reflow tool: every word becomes "the word, followed by a newline",
    // and the untouched whitespace between words is dropped instead of
    // being copied through.
    std::string headline{"Regex makes text processing easy"};
    std::regex one_word{R"(([\w]+))"};
    std::string one_per_line{std::regex_replace(headline, one_word, "$1\n",
        std::regex_constants::format_no_copy)};

    std::println("\nreflowed one word per line:\n{}", one_per_line);

    return 0;
}
