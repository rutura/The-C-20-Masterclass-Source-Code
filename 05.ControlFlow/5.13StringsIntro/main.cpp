#include <print>
#include <string>

int main() {

    // std::string holds text of any length and manages its own memory.
    std::string base{"report"};
    std::string extension{".pdf"};
    std::string suffix{};                     // an empty string, length 0

    // length() / size() - the two names do the same thing.
    std::println("base      : \"{}\", length {}", base, base.length());
    std::println("extension : \"{}\", length {}", extension, extension.length());
    std::println("suffix    : \"{}\", length {}", suffix, suffix.length());

    // empty() - true when there are no characters.
    std::println("suffix.empty() : {}", suffix.empty());

    // Compare with == and != , just like numbers.
    std::println("base == extension : {}", base == extension);
    std::println("base != extension : {}", base != extension);

    // + joins strings into a new one (concatenation).
    std::string filename{base + extension};
    std::println("base + extension : \"{}\"", filename);

    // C++20 added starts_with / ends_with for quick prefix/suffix checks.
    std::println("filename starts with \"report\" : {}", filename.starts_with("report"));
    std::println("filename ends with \".pdf\"     : {}", filename.ends_with(".pdf"));

    return 0;
}
