#include <fmt/format.h>

consteval int get_value(){
    return 3;
}

int main(){
    constexpr int value = get_value();
    fmt::println( "value : {}" , value);
    return 0;
}