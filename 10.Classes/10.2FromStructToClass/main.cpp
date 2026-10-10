#include <print>
#include <string>

// A struct from earlier chapters: all its data is public, so anyone, anywhere,
// can put it in a state that makes no sense.
struct PlainSensor {
    std::string name;
    double offset;          // calibration offset in degrees, meant to stay between -5 and +5
};

// A class bundles the data WITH the functions that are allowed to change it,
// and hides the data. Code outside the class can only go through the public
// functions, so the rule "the offset stays between -5 and +5" is written once,
// in one place, and cannot be bypassed.
class Sensor {
public:
    void set_name(const std::string& name) {
        name_ = name;
    }

    // The const after the parameter list says "this function does not change
    // the sensor". 10.5 explains it. For now, read it as "this one only looks".
    const std::string& name() const {
        return name_;
    }

    void set_offset(double offset) {
        if (offset < -5.0 || offset > 5.0) {
            std::println("  rejected offset {}: it must be between -5 and 5", offset);
            return;                       // the object keeps its previous, valid value
        }
        offset_ = offset;
    }

    double offset() const {
        return offset_;
    }

    double calibrated(double raw) const {
        return raw + offset_;
    }

private:
    // A trailing underscore is a common way to tell a member from a local
    // variable or parameter at a glance. Default member initializers give a
    // fresh Sensor a sensible state before anyone sets anything.
    std::string name_{"unnamed"};
    double offset_{0.0};
};

int main() {

    // With the struct, nothing stops nonsense.
    PlainSensor plain{"sensor-3", 0.0};
    plain.offset = 400.0;
    std::println("PlainSensor {} has offset {} (and nobody complained)", plain.name, plain.offset);

    // With the class, the same attempt is refused.
    Sensor sensor;
    sensor.set_name("sensor-12");
    sensor.set_offset(1.5);
    std::println("\nSensor {} has offset {}", sensor.name(), sensor.offset());

    sensor.set_offset(400.0);
    std::println("after the bad call it still has offset {}", sensor.offset());

    std::println("a raw 70.0 reads as {} after calibration", sensor.calibrated(70.0));

    // Private means private: neither of these lines compiles.
    //     sensor.offset_ = 400.0;      // error: 'offset_' is private
    //     sensor.name_ = "";           // error: 'name_' is private

    // The only technical difference between struct and class is the DEFAULT
    // access: members of a struct are public until you say otherwise, members
    // of a class are private. The habit that goes with it: a struct for plain
    // data that has no rules, a class for something that must stay valid.
    return 0;
}
