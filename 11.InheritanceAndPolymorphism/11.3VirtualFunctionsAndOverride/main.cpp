#include <print>
#include <string>

class Sensor {
public:
    // virtual: "decide which version to run when the program RUNS, by looking
    // at the real type of the object, not at the type of the variable".
    virtual double read() const { return 0.0; }
    virtual std::string label() const { return "generic sensor"; }

    // NOT virtual: the version is chosen by the declared type, at compile time.
    std::string kind() const { return "sensor"; }

    virtual ~Sensor() = default;           // 11.6 explains why this is needed
};

class TemperatureSensor : public Sensor {
public:
    // override: "I mean to replace a virtual function of the base". The
    // compiler checks that one with the same signature exists, and refuses if not.
    double read() const override { return 21.5; }
    std::string label() const override { return "temperature sensor"; }

    // Same name as the non-virtual Sensor::kind, so this HIDES it, it does not
    // override it. The two are unrelated functions.
    std::string kind() const { return "temperature sensor"; }
};

class WindSensor : public Sensor {
public:
    double read() const override { return 12.0; }
    std::string label() const override { return "wind sensor"; }
};

// A class marked final cannot be derived from. A single function can be marked
// final too, and then it cannot be overridden any further.
class FrozenSensor final : public Sensor {
public:
    std::string label() const override { return "frozen sensor"; }
};

// This function knows only about the base class, through a reference. The
// calls below show which ones follow the real type of the object.
void inspect(const Sensor& sensor) {
    std::println("  kind()  = {}   (non-virtual: follows the declared type, Sensor)", sensor.kind());
    std::println("  label() = {}   (virtual: follows the real type)", sensor.label());
    std::println("  read()  = {}   (virtual: follows the real type)", sensor.read());
}

int main() {

    TemperatureSensor temperature;
    WindSensor wind;
    Sensor generic;

    std::println("calling through a Sensor reference:");
    std::println("a TemperatureSensor:");
    inspect(temperature);
    std::println("a WindSensor:");
    inspect(wind);
    std::println("a plain Sensor:");
    inspect(generic);

    // Called directly on the derived object, the compiler knows the real type
    // and the derived kind() wins. HIDING only shows up through the base.
    std::println("\ntemperature.kind() called directly = {}", temperature.kind());

    // What "override" protects you from. Each of these compiles WITHOUT the
    // keyword, as a brand new function that overrides nothing, and silently
    // never gets called through the base:
    //
    //     double read() override;              // error: missing const, no such function in the base
    //     std::string Label() const override;  // error: a typo in the name
    //
    // With the keyword the compiler stops you. Always write it.

    // final in action:
    //     class SuperFrozen : public FrozenSensor {};     // error: FrozenSensor is final
    FrozenSensor frozen;
    std::println("\nfrozen sensor says: {}", frozen.label());

    return 0;
}
