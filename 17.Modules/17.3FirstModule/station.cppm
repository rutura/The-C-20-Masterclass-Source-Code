// A module interface unit. The first line declares the module this file defines.
export module station;

// A macro defined in a module stays in the module. It is not exported.
#define STATION_WARM_LIMIT 25.0

// `export` makes a name visible to whoever imports the module. Everything
// without it is private to the module.
export struct Reading {
    int hour;
    double celsius;
};

export constexpr double warm_limit{STATION_WARM_LIMIT};

export double to_fahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

// Not exported: a detail of the module that importers cannot even name.
double calibration_offset() {
    return 0.5;
}

export double calibrated(double celsius) {
    return celsius + calibration_offset();
}

export bool is_warm(const Reading& reading) {
    return calibrated(reading.celsius) >= STATION_WARM_LIMIT;
}
