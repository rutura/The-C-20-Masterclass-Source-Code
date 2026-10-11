#include <print>

import legacy;

int main() {
    Calibration roof{0.5, 1.0};

    std::println("21.0 raw is {} calibrated", apply(roof, 21.0));
    std::println("0 C is {} K", celsius_to_kelvin(0.0));
    std::println("the header's version, as a constant: {}", legacy_version);

    // The macro itself does not cross the module:
    //
    //     std::println("{}", LEGACY_VERSION);        // error: LEGACY_VERSION is not declared here
    return 0;
}
