#include <memory>
#include <print>
#include <string>
#include <vector>

class Sensor {
public:
    explicit Sensor(const std::string& name) : name_{name} {}
    virtual ~Sensor() = default;

    virtual double read() const { return 0.0; }
    virtual std::string label() const { return "generic sensor"; }
    const std::string& name() const { return name_; }

private:
    std::string name_;
};

class TemperatureSensor : public Sensor {
public:
    explicit TemperatureSensor(const std::string& name) : Sensor{name} {}
    double read() const override { return 21.5; }
    std::string label() const override { return "temperature sensor"; }
};

class WindSensor : public Sensor {
public:
    explicit WindSensor(const std::string& name) : Sensor{name} {}
    double read() const override { return 12.0; }
    std::string label() const override { return "wind sensor"; }

    double gust() const { return 18.5; }              // only a WindSensor has this
};

int main() {

    // The point of polymorphism: ONE container, ONE loop, and every element
    // behaves as its own type. The elements are pointers (here, owning
    // unique_ptrs) to the base class, so each can really be a derived object.
    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.push_back(std::make_unique<TemperatureSensor>("north"));
    sensors.push_back(std::make_unique<WindSensor>("roof"));
    sensors.push_back(std::make_unique<Sensor>("spare"));
    sensors.push_back(std::make_unique<TemperatureSensor>("east"));

    std::println("one loop, four sensors, three kinds:");
    for (const auto& sensor : sensors) {
        std::println("  {:<6} {:<20} reads {}", sensor->name(), sensor->label(), sensor->read());
    }

    // SLICING. Copy a derived object into a base object BY VALUE, and the
    // derived part is cut off: what is left is a plain Sensor, so the virtual
    // functions now run the base versions.
    WindSensor wind{"mast"};
    Sensor sliced{wind};

    std::println("\noriginal: {} reads {}", wind.label(), wind.read());
    std::println("sliced:   {} reads {}   <- a plain Sensor, the wind part is gone", sliced.label(), sliced.read());

    // The same thing happens in a vector of base OBJECTS. There is room in each
    // slot for a Sensor only, so whatever is pushed in is sliced to fit.
    std::vector<Sensor> by_value;
    by_value.push_back(wind);
    by_value.push_back(TemperatureSensor{"copy"});
    std::println("\nvector<Sensor> of the same two:");
    for (const Sensor& sensor : by_value) {
        std::println("  {:<6} {}", sensor.name(), sensor.label());
    }

    // The cure: never copy a polymorphic object into a base-class VALUE. Use a
    // reference, a pointer or a smart pointer, which refer to the real object.
    const Sensor& by_reference{wind};
    std::println("\nthrough a reference: {} reads {}", by_reference.label(), by_reference.read());

    // And the other direction: a base pointer can only call what the base
    // declares. gust() exists only in WindSensor, so this does not compile:
    //     sensors[1]->gust();                    // error: Sensor has no member 'gust'
    // 11.10 shows how to ask "is this one really a WindSensor?".
    return 0;
}
