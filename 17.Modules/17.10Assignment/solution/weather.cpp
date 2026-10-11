module;

#include <format>
#include <string>

module weather;

import :detail;                    // only an implementation unit imports an internal partition

std::string describe(const Reading& reading) {
    return std::format("{}h: {} C, {}", reading.hour, reading.celsius, label_for(reading.celsius));
}
