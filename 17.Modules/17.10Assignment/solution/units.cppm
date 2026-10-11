export module units;

// Not exported: a detail of the module.
double kelvin_offset() {
    return 273.15;
}

export double to_fahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

export double to_kelvin(double celsius) {
    return celsius + kelvin_offset();
}
