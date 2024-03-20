#include <fmt/format.h>

/*
 * Cppreference:
 * consteval: https://en.cppreference.com/w/cpp/language/consteval
 */
consteval int get_value(){
    return 3;
}

int main(){
    constexpr int value = get_value();
    fmt::println("Value: {}", value);
    return 0;
}