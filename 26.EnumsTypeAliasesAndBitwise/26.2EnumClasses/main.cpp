#include <print>

// enum class defaults its underlying type to int, but a small, bounded set
// of values like months fits in a single byte - spelling out the underlying
// type keeps the enum as small as what it actually represents.
enum class Month : char {
    Jan = -1, January = Jan, Feb, Mar,
    Apr, May, Jun,
    Jul, Aug, Sep,
    Oct = 100, Nov, Dec
};

int main() {

    Month month{Month::Jan};
    std::println("month : {}", static_cast<int>(month));
    std::println("sizeof(month) : {}", sizeof(month));

    return 0;
}