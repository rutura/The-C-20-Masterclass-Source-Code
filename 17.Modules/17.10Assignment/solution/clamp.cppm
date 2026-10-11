export module clamp;

// A template goes entirely in the interface.
export template <typename T>
T clamped(T value, T low, T high) {
    return value < low ? low : (value > high ? high : value);
}
