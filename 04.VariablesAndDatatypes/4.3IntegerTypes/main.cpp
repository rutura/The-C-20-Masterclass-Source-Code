#include <print>
#include <cstdint>

int main() {

    // Different stats in our arcade tracker need different amounts of room to
    // store their values, so C++ gives us several integer types to choose
    // from - each one a different size in memory (checked here with sizeof).

    // The current level fits comfortably in a small range, so a short is enough.
    short currentLevel{7};

    // The high score is a bigger, everyday number - int is the natural default.
    int highScore{1'000'000};

    // Total coins fed into the cabinet over its lifetime can climb into the
    // billions, which overflows an int - long long gives us far more headroom.
    long long lifetimeCoinsInserted{9'000'000'000};

    std::println("currentLevel          : {} ({} bytes)", currentLevel, sizeof(currentLevel));
    std::println("highScore             : {} ({} bytes)", highScore, sizeof(highScore));
    std::println("lifetimeCoinsInserted : {} ({} bytes)", lifetimeCoinsInserted, sizeof(lifetimeCoinsInserted));

    // Every integer type above is "signed" by default - it can represent
    // negative values too. Some stats, like a count of coins, can never
    // sensibly go negative, so we can mark the type "unsigned" instead and get
    // a bit more positive range out of the same number of bytes.
    unsigned int coinsInMachine{250};
    std::println("coinsInMachine        : {} ({} bytes)", coinsInMachine, sizeof(coinsInMachine));

    // unsigned int negativeAttempt{-5}; // compiler error: can't store a negative value

    // Watch out: unsigned subtraction never goes negative - it wraps around
    // instead, which is a classic source of arcade-tracker bugs.
    unsigned int coinsAfterRefund{coinsInMachine - 300};
    std::println("coinsInMachine - 300  : {} (wrapped around, not -50!)", coinsAfterRefund);

    // Writing out "short", "unsigned int", "long long" etc. describes a size
    // in *bytes*, but the exact number of bytes those keywords map to can
    // differ across platforms and compilers. When we need a guaranteed exact
    // width - for save-file formats, network messages, or just to be precise -
    // <cstdint> gives us fixed-width aliases instead, which is the modern,
    // more portable way to say "I need exactly this many bits".
    std::int16_t compactLevel{7};        // guaranteed 16 bits, same value as currentLevel
    std::int32_t portableHighScore{1'000'000};
    std::uint32_t portableCoinsInMachine{250};

    std::println("");
    std::println("compactLevel (int16_t)          : {} ({} bytes)", compactLevel, sizeof(compactLevel));
    std::println("portableHighScore (int32_t)     : {} ({} bytes)", portableHighScore, sizeof(portableHighScore));
    std::println("portableCoinsInMachine (uint32_t): {} ({} bytes)", portableCoinsInMachine, sizeof(portableCoinsInMachine));

    return 0;
}
