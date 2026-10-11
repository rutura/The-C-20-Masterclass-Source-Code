import std;                        // the whole standard library, in one line

int main() {
    std::vector<double> temperatures{18.5, 24.0, 21.5, 12.0};
    std::ranges::sort(temperatures);

    std::map<std::string, double> latest{{"north", 18.5}, {"south", 24.0}};
    std::optional<double> missing;

    std::println("sorted: {} .. {}", temperatures.front(), temperatures.back());
    std::println("south is {}", latest.at("south"));
    std::println("missing has a value: {}", missing.has_value());
    std::println("largest int: {}", std::numeric_limits<int>::max());
    std::println("a string of {} letters", std::string{"north"}.size());

    // Macros are not part of a module, so the standard ones are not imported:
    //
    //     std::println("{}", INT_MAX);        // INT_MAX is a macro of <climits>
    //     assert(temperatures.size() > 0);    // assert is a macro of <cassert>
    //
    // Use std::numeric_limits<int>::max() and static_assert, or put the
    // #include of the header in front of your code.
    return 0;
}
