#include <cstdint>
#include <print>
#include <string_view>

// An enum class gives a fixed set of named values their own type. Unlike
// plain C enums, the names are scoped (Direction::North, not just North)
// and they do not silently convert to int - you have to ask.

enum class Direction : std::uint8_t {   // pin the storage to one byte
    North,                              // 0
    East,                               // 1
    South,                              // 2
    West,                               // 3
};

enum class LogLevel {                   // default underlying type is int
    Debug,
    Info,
    Warning,
    Error,
};

std::string_view to_text(Direction d) {
    // C++20 `using enum` pulls the enumerators into scope for this block,
    // so the switch reads `North` instead of `Direction::North` five times.
    using enum Direction;
    switch (d) {
        case North: return "north";
        case East:  return "east";
        case South: return "south";
        case West:  return "west";
    }
    return "unknown";
}

int main() {
    Direction heading{Direction::East};
    std::println("heading      : {}", to_text(heading));

    // No implicit conversion to int - this is the safety. Ask with a cast.
    std::println("as number    : {}", static_cast<int>(heading));
    std::println("storage bytes: {}", sizeof(Direction));   // 1, thanks to : std::uint8_t

    // int -> enum also needs an explicit cast. Only do this when you know
    // the value is a valid enumerator (here, 2 -> South).
    int raw{2};
    Direction from_raw{static_cast<Direction>(raw)};
    std::println("from raw {}   : {}", raw, to_text(from_raw));

    // Enums compare with == and <, and work as switch labels (above).
    LogLevel current{LogLevel::Warning};
    if (current >= LogLevel::Warning) {
        std::println("log level is Warning or worse");
    }

    // Rotate through the compass by going via the underlying integer.
    for (int i{0}; i < 4; ++i) {
        Direction d{static_cast<Direction>(i)};
        std::println("  {} -> {}", i, to_text(d));
    }

    return 0;
}
