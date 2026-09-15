#include <print>
#include <regex>
#include <string>

int main() {

    // regex_replace rewrites every match in a copy of the string - the
    // original is untouched.
    std::string data{"1\t2\t3\t4"};
    std::println("Before replacing tabs with commas: {}", data);
    std::string csv_line{std::regex_replace(data, std::regex{"\t"}, ",")};
    std::println("after replacing tabs with commas: {}", csv_line);
    std::println("Data is unchanged after replacement: {}", data);
    

    // The replacement string can reference capture groups with $1, $2, ...
    // Here group 1 is the header text, group 2 is the paragraph text.
    std::string html{"<body><h1>Header</h1><p>Some text</p></body>"};
    std::regex tags{"<h1>(.*)</h1><p>(.*)</p>"};
    std::string replacement{"H1=$1 and P=$2"};

    std::string default_result{std::regex_replace(html, tags, replacement)};
    std::println("\noriginal:        '{}'", html);
    std::println("default replace: '{}'", default_result);

    // format_no_copy drops everything that did NOT match instead of
    // copying it through untouched - only the replaced text survives.
    std::string no_copy_result{std::regex_replace(html, tags, replacement,
        std::regex_constants::format_no_copy)};
    std::println("format_no_copy:  '{}'", no_copy_result);

    // Combining a capture group with format_no_copy turns replace into a
    // reflow tool: every word becomes "the word, followed by a newline",
    // and the untouched whitespace between words is dropped instead of
    // being copied through.
    std::string paragraph{"This is a test string."};
    std::regex one_word{R"(([\w]+))"};
    std::string one_per_line{std::regex_replace(paragraph, one_word, "$1\n",
        std::regex_constants::format_no_copy)};

    std::println("\nreflowed one word per line:\n{}", one_per_line);

    return 0;
}
