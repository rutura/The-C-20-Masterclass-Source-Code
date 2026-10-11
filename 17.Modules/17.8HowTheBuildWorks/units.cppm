export module units;

export constexpr double to_fahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}
