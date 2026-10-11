export module limits;

#define COMFORT_LOW 18.0                    // macros are never exported
#define COMFORT_HIGH 26.0

export struct Range {
    double low;
    double high;
};

export constexpr Range comfortable{COMFORT_LOW, COMFORT_HIGH};

export constexpr bool within(const Range& range, double value) {
    return value >= range.low && value <= range.high;
}
