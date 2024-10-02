/*
    . This file contains code that showcases an example of weak ordering.
    . CaseInsensitiveString is a class that compares two strings in a case-insensitive manner.
    . Just because two case insensitive strings are equivalent doesn't mean they are the same.
*/
module;

#include <string>
#include <compare>
#include <fmt/format.h>

export module ordering_2;

namespace ordering_2{

    // Weak ordering example 2
    std::weak_ordering case_insensitive_compare(const char *str1, const char *str2) {
        // Turn them all to uppercase
        std::string string1(str1);
        std::string string2(str2);

        for (auto &c : string1) {
            c = toupper(c);
        }

        for (auto &c : string2) {
            c = toupper(c);
        }

        int cmp = string1.compare(string2);
        if (cmp > 0)
            return std::weak_ordering::greater;
        else if (cmp == 0)
            return std::weak_ordering::equivalent;
        else
            return std::weak_ordering::less;
    }

    class CaseInsensitiveString {
    public:
        CaseInsensitiveString(const std::string &str) : s(str) {}

        std::weak_ordering operator<=>(const CaseInsensitiveString &b) const {
            return case_insensitive_compare(s.c_str(), b.s.c_str());
        }

        std::weak_ordering operator<=>(const char *b) const {
            return case_insensitive_compare(s.c_str(), b);
        }

        bool operator==(const CaseInsensitiveString &right_operand) const {
            return (case_insensitive_compare(s.c_str(), right_operand.s.c_str()) == std::weak_ordering::equivalent);
        }

    private:
        std::string s;
    };

    export void weak_ordering_ex2() {
        CaseInsensitiveString ci_str1("Hello");
        CaseInsensitiveString ci_str2("ZELLO");

        fmt::println("ci_str1 <= ci_str2 : {}", (ci_str1 <= ci_str2));
        fmt::println("ci_str1 <= Kello : {}", (ci_str1 <= "Kello"));
        fmt::println("Kello <= ci_str2 : {}", ("Kello" <= ci_str2));

        // You need to put in a == operator. Compiler won't generate one for you.
        fmt::println("ci_str1 == ci_str2 : {}", (ci_str1 == ci_str2));
    }
} // namespace ordering_2