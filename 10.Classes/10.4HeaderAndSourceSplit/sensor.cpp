#include "sensor.h"

#include <format>

// The source file holds the DEFINITIONS. Each one starts with "Sensor::", the
// scope resolution operator, which says "this function belongs to the class
// Sensor". Without the prefix it would be an unrelated free function.

Sensor::Sensor(int id, const std::string& name, double offset)
    : id_{id}, name_{name}, offset_{offset} {}

const std::string& Sensor::name() const {
    return name_;
}

double Sensor::offset() const {
    return offset_;
}

void Sensor::set_offset(double offset) {
    if (offset >= -5.0 && offset <= 5.0) {
        offset_ = offset;
    }
}

double Sensor::calibrated(double raw) const {
    return raw + offset_;
}

std::string Sensor::describe() const {
    return std::format("Sensor #{} '{}' (offset {:+.1f})", id_, name_, offset_);
}
