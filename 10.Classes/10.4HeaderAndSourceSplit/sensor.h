#pragma once

#include <string>

// The header holds the DECLARATION: what a Sensor is and what you can do with
// it. Anyone who uses Sensor includes this file and nothing else.
class Sensor {
public:
    Sensor(int id, const std::string& name, double offset = 0.0);

    // Tiny functions can be defined right here, inside the class. They are
    // implicitly inline, so the compiler may paste them into the caller.
    int id() const { return id_; }

    // Larger ones are only declared here and defined in sensor.cpp.
    const std::string& name() const;
    double offset() const;
    void set_offset(double offset);
    double calibrated(double raw) const;
    std::string describe() const;

private:
    int id_;
    std::string name_;
    double offset_;
};
