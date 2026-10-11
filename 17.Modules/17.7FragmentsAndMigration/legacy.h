#pragma once

// An existing header, as it might sit in a project that is being migrated.
#define LEGACY_VERSION 3                    // a macro: it will NOT cross a module boundary

struct Calibration {
    double offset;
    double scale;
};

double celsius_to_kelvin(double celsius);
double apply(const Calibration& calibration, double raw);
