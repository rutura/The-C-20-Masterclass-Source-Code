#include <print>
#include <string>

int main() {

    // std::string holds text of any length and manages its own memory.
    std::string first{"happy"};
    std::string second{" birthday"};
    std::string empty_one{};                 // an empty string, length 0

    // length() / size() - the two names do the same thing.
    std::println("first  : \"{}\", length {}", first, first.length());
    std::println("second : \"{}\", length {}", second, second.length());
    std::println("empty  : \"{}\", length {}", empty_one, empty_one.length());

    // empty() - true when there are no characters.
    std::println("empty_one.empty() : {}", empty_one.empty());

    // Compare with == and != , just like numbers.
    std::println("first == second : {}", first == second);
    std::println("first != second : {}", first != second);

    // + joins strings into a new one (concatenation).
    std::string phrase{first + second};
    std::println("first + second : \"{}\"", phrase);

    // C++20 added starts_with / ends_with for quick prefix/suffix checks.
    std::println("phrase starts with \"happy\" : {}", phrase.starts_with("happy"));
    std::println("phrase ends with \"day\"     : {}", phrase.ends_with("day"));

    return 0;
}
