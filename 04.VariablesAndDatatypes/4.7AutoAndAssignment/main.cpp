#include <print>

int main() {

    // auto asks the compiler to work out a variable's type from its
    // initializer, instead of us spelling the type out ourselves. Literal
    // suffixes (u, l, f, ...) still steer which type gets deduced.
    auto level{7};             // int
    auto highScore{1'000'000}; // int
    auto accuracy{93.33f};     // float, thanks to the f suffix
    auto initial{'A'};         // char
    auto lifetimeCoins{9'000'000'000ll}; // long long, thanks to the ll suffix

    std::println("level        occupies {} bytes", sizeof(level));
    std::println("highScore    occupies {} bytes", sizeof(highScore));
    std::println("accuracy     occupies {} bytes", sizeof(accuracy));
    std::println("initial      occupies {} bytes", sizeof(initial));
    std::println("lifetimeCoins occupies {} bytes", sizeof(lifetimeCoins));

    // The {...} braces above are *initializing* the variable - giving it its
    // very first value, at the moment it's created. A separate "=" without
    // braces later on is an *assignment* - replacing a value the variable
    // already has.
    std::println("");
    std::println("highScore before assignment: {}", highScore);
    highScore = 1'250'000; // assignment: highScore already existed
    std::println("highScore after assignment : {}", highScore);

    // Braced initialization refuses to silently throw away information -
    // this is called a narrowing conversion, and it won't compile:
    // int narrowed{93.33}; // compiler error: double doesn't fit losslessly in int

    // Plain assignment offers no such protection, which is exactly why we
    // reach for braces `{}` when declaring variables throughout this course.
    int narrowedScore = 93.33; // compiles, but silently truncates to 93
    std::println("narrowedScore (truncated): {}", narrowedScore);

    // auto deduces a type once, at initialization - it doesn't update if you
    // later assign something that would have deduced differently. Assigning a
    // negative number into an auto that deduced unsigned wraps around instead
    // of going negative, same as we saw with unsigned int earlier.
    auto coinsInMachine{250u}; // deduced: unsigned int
    coinsInMachine = -10;      // DANGER: no negative unsigned values, this wraps around
    std::println("");
    std::println("coinsInMachine after -10: {}", coinsInMachine);

    return 0;
}
