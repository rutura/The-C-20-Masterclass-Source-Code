/*
    . This file contains code that showcases an example of weak ordering.
    . We are comparing two strings based on their length.
    . If the strings have the same length, they are equivalent.
    . Equivalence doesn't mean that the strings are the same: have the same content.
*/
module;

#include <string>
#include <compare>
#include <fmt/format.h>

export module ordering_1;

namespace ordering_1 {

    //#1: Weak ordering example1
    class ComparableString
    {
    public:
    ComparableString(const std::string &str) : m_str{ str } {}

    std::weak_ordering operator<=>(const ComparableString &right_side) const
    {

        if (m_str.size() == right_side.m_str.size()) {
        return std::weak_ordering::equivalent;
        } else if (m_str.size() > right_side.m_str.size()) {
        return std::weak_ordering::greater;
        } else {
        return std::weak_ordering::less;
        }
    }

    bool operator==(const ComparableString &right_side) const { return (m_str.size() == right_side.m_str.size()); }

    private:
    std::string m_str;
    };

    export void weak_ordering_ex1(){
        ComparableString cmp_str1("Fog");
        ComparableString cmp_str2("Dogy");

        fmt::println("cmp_str1 > cmp_str2 : {}", (cmp_str1 > cmp_str2));
        fmt::println("cmp_str1 < cmp_str2 : {}", (cmp_str1 < cmp_str2));

        fmt::println("cmp_str1 == cmp_str2 : {}", (cmp_str1 == cmp_str2));
    }

}   // namespace ordering_1