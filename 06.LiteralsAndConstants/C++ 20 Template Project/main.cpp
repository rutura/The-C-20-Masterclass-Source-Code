#include <fmt/format.h>

/*
 * Cppreference:
 * consteval: https://en.cppreference.com/w/cpp/language/consteval
 */
consteval int get_value(){
    return 3;
}
// if consteval
int get_3_or_30() {
    /*if consteval {
        return get_value();
    }
    return 30;*/
    if(std::is_constant_evaluated()) {
        return get_value();
    }
    return 30;
}

constexpr int get_3_or_30_constexpr() {
    /*if consteval {
        return get_value();
    }
    return 30;*/
    if(std::is_constant_evaluated()) {
        return get_value();
    }
    return 30;
}

int main(){
    constexpr int value = get_value();
    fmt::println("Value: {}", value);
    auto value_3_or_30 = get_3_or_30();
    fmt::println("Value 3 or 30(not constexpr): {}", value_3_or_30);
    auto value_3_or_30_constexpr = get_3_or_30_constexpr();
    fmt::println("Value 3 or 30(constexpr): {}", value_3_or_30_constexpr);
    return 0;
}