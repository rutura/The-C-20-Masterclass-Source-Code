#include <memory>
#include <print>
#include <string>
#include <typeinfo>
#include <vector>

class Sensor {
public:
    virtual ~Sensor() = default;                  // RTTI needs a polymorphic base
    virtual std::string label() const { return "sensor"; }
};

class TemperatureSensor : public Sensor {
public:
    std::string label() const override { return "temperature sensor"; }
    double calibration_offset() const { return 1.5; }        // only a TemperatureSensor has this
};

// A class derived from a class derived from Sensor.
class ArcticSensor : public TemperatureSensor {
public:
    std::string label() const override { return "arctic sensor"; }
};

class WindSensor : public Sensor {
public:
    std::string label() const override { return "wind sensor"; }
    double gust() const { return 18.5; }                      // only a WindSensor has this
};

int main() {

    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.push_back(std::make_unique<TemperatureSensor>());
    sensors.push_back(std::make_unique<WindSensor>());
    sensors.push_back(std::make_unique<Sensor>());
    sensors.push_back(std::make_unique<WindSensor>());
    sensors.push_back(std::make_unique<ArcticSensor>());

    // dynamic_cast: "is this base pointer REALLY pointing at a WindSensor?".
    // The check happens at run time, using the type information (RTTI) that
    // every polymorphic object carries. On success you get a pointer to the
    // derived type. On failure, a null pointer.
    std::println("looking for wind sensors in the list:");
    for (const auto& sensor : sensors) {
        if (const auto* wind{dynamic_cast<const WindSensor*>(sensor.get())}) {
            std::println("  {} found, gust {}", wind->label(), wind->gust());
        }
        else {
            std::println("  {} is not a wind sensor", sensor->label());
        }
    }

    // typeid names the exact type of an object, through the base reference.
    // Comparing two typeids tells you whether the real types are IDENTICAL.
    const Sensor& temperature{*sensors[0]};
    const Sensor& arctic{*sensors[4]};

    std::println("\nsensors[0] is exactly a TemperatureSensor: {}", typeid(temperature) == typeid(TemperatureSensor));
    std::println("sensors[4] is exactly a TemperatureSensor: {}", typeid(arctic) == typeid(TemperatureSensor));

    // dynamic_cast is looser: it also succeeds for a class DERIVED from the
    // target. An ArcticSensor is not exactly a TemperatureSensor, but it IS one.
    const auto* as_temperature{dynamic_cast<const TemperatureSensor*>(sensors[4].get())};
    std::println("sensors[4] converts to a TemperatureSensor*: {}", as_temperature != nullptr);
    if (as_temperature != nullptr) {
        std::println("  and its calibration offset is {}", as_temperature->calibration_offset());
    }

    // static_cast to a derived type is checked ONLY at compile time. If you are
    // wrong, nothing stops you, and the result is undefined behaviour:
    //     auto* wrong{static_cast<WindSensor*>(sensors[0].get())};   // compiles, a lie
    //     wrong->gust();                                              // undefined
    // Use dynamic_cast whenever you are not sure.

    // A reference cast has no "null" to return, so on failure it throws
    // std::bad_cast (chapter 13 covers exceptions):
    //     const auto& wind{dynamic_cast<const WindSensor&>(temperature)};   // throws: it is not one

    // The design warning. Every dynamic_cast is a little admission that the
    // base class did not offer what the caller needed. Before writing one, ask:
    // should this be a virtual function on Sensor instead?
    //
    //     asking the object what it is, then acting  ->  ask the object to act
    //     if (is a WindSensor) print gust            ->  virtual void print_details()
    //
    // Casts are for the cases where that is not possible, such as code you
    // cannot change.
    return 0;
}
