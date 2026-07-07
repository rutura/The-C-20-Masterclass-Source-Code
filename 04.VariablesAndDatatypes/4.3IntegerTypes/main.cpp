#include <print>
#include <cstdint>

int main() {

    // Different numbers in our expense tracker need different amounts of room
    // to store their values, so C++ gives us several integer types to choose
    // from - each one a different size in memory (checked here with sizeof).

    // The number of expenses logged today fits comfortably in a small range,
    // so a short is enough.
    short expensesLoggedToday{7};

    // A transaction id is a bigger, everyday number - int is the natural default.
    int transactionId{1'000'000};

    // The total amount of money (in cents) a business processes over its
    // lifetime can climb into the billions, which overflows an int -
    // long long gives us far more headroom.
    long long lifetimeCentsProcessed{9'000'000'000};

    std::println("expensesLoggedToday    : {} ({} bytes)", expensesLoggedToday, sizeof(expensesLoggedToday));
    std::println("transactionId          : {} ({} bytes)", transactionId, sizeof(transactionId));
    std::println("lifetimeCentsProcessed : {} ({} bytes)", lifetimeCentsProcessed, sizeof(lifetimeCentsProcessed));

    // Every integer type above is "signed" by default - it can represent
    // negative values too. Some numbers, like a count of receipts on file,
    // can never sensibly go negative, so we can mark the type "unsigned"
    // instead and get a bit more positive range out of the same number of bytes.
    unsigned int receiptsOnFile{250};
    std::println("receiptsOnFile         : {} ({} bytes)", receiptsOnFile, sizeof(receiptsOnFile));

    // unsigned int negativeAttempt{-5}; // compiler error: can't store a negative value

    // Watch out: unsigned subtraction never goes negative - it wraps around
    // instead, which is a classic source of expense-tracker bugs.
    unsigned int receiptsAfterVoiding{receiptsOnFile - 300};
    std::println("receiptsOnFile - 300   : {} (wrapped around, not -50!)", receiptsAfterVoiding);

    // Writing out "short", "unsigned int", "long long" etc. describes a size
    // in *bytes*, but the exact number of bytes those keywords map to can
    // differ across platforms and compilers. When we need a guaranteed exact
    // width - for save-file formats, network messages, or just to be precise -
    // <cstdint> gives us fixed-width aliases instead, which is the modern,
    // more portable way to say "I need exactly this many bits".
    std::int16_t compactExpenseCount{7};        // guaranteed 16 bits, same value as expensesLoggedToday
    std::int32_t portableTransactionId{1'000'000};
    std::uint32_t portableReceiptsOnFile{250};

    std::println("");
    std::println("compactExpenseCount (int16_t)     : {} ({} bytes)", compactExpenseCount, sizeof(compactExpenseCount));
    std::println("portableTransactionId (int32_t)   : {} ({} bytes)", portableTransactionId, sizeof(portableTransactionId));
    std::println("portableReceiptsOnFile (uint32_t) : {} ({} bytes)", portableReceiptsOnFile, sizeof(portableReceiptsOnFile));

    return 0;
}
