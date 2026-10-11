#include <print>

import station;                    // instead of #include "station.h"

int main() {
    Reading noon{12, 24.7};
    Reading morning{6, 11.0};

    std::println("noon is {} F, calibrated {} C", to_fahrenheit(noon.celsius), calibrated(noon.celsius));
    std::println("warm limit is {}", warm_limit);
    std::println("noon is warm: {}   morning is warm: {}", is_warm(noon), is_warm(morning));

    // These do not compile. Try them one at a time.
    //
    //     std::println("{}", calibration_offset());      // not exported: the name does not exist here
    //     std::println("{}", STATION_WARM_LIMIT);        // macros are never exported
    return 0;
}
