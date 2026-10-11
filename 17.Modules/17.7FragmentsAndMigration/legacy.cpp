// The implementation stays an ORDINARY source file that includes the header.
// Nothing about it changes when the header gets a module wrapper.
#include "legacy.h"

double celsius_to_kelvin(double celsius) {
    return celsius + 273.15;
}

double apply(const Calibration& calibration, double raw) {
    return raw * calibration.scale + calibration.offset;
}
