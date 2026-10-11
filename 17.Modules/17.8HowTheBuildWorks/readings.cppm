export module readings;

import units;                      // readings depends on units

export struct Reading {
    int hour;
    double celsius;

    double fahrenheit() const { return to_fahrenheit(celsius); }
};
