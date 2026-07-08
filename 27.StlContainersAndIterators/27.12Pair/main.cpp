#include <print>
#include <utility>
#include <vector>

int main() {

    std::println("creating pairs:");
    std::pair<int, std::string> pair1{0, "Book shelf"};
    auto pair2 = std::make_pair(1, "Table"); // deduces the template arguments

    std::println("pair1 : ({},{})", pair1.first, pair1.second);
    std::println("pair2 : ({},{})", pair2.first, pair2.second);

    std::println("");
    std::println("auto[] syntax - collect components of a pair into variables : ");
    auto [int_var, string_var] = pair1;
    std::println("pair1 (auto[] syntax) : ({},{})", int_var, string_var);

    std::println("");
    std::println("template argument deduction : ");
    std::pair student(33165, std::string("John Snow")); // C++17 CTAD, no explicit types needed

    std::println("student ID : {}", student.first);
    std::println("Student name : {}", student.second);

    std::println("");
    std::println("collection of pairs : ");
    std::vector<std::pair<int, std::string>> collection{
        {10, "Earth"}, {20, "Spins"}, {30, "From"}, {40, "Left"}, {50, "To"}, {60, "Right"}};

    std::println("");
    std::println("syntax1 : ");
    std::print("collection : [");
    for (const auto& elt : collection) {
        std::print(" ({},{})", elt.first, elt.second);
    }
    std::println("]");

    std::println("");
    std::println("syntax2 : ");
    std::print("collection : [");
    for (auto [key, value] : collection) {
        std::print(" ({},{})", key, value);
    }
    std::println("]");

    return 0;
}
