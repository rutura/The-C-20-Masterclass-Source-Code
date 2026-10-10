#include <format>
#include <print>
#include <string>

// The BASE class: what every sensor has in common.
class Sensor {
public:
    Sensor(int id, const std::string& name)
        : id_{id}, name_{name} {
        std::println("  Sensor {} constructed", name_);
    }

    // Not virtual, which is fine ONLY because nothing in this program ever
    // deletes a derived object through a Sensor pointer. 11.6 shows what goes
    // wrong when something does, and why a base class meant for that gets a
    // virtual destructor.
    ~Sensor() {
        std::println("  Sensor {} destroyed", name_);
    }

    int id() const { return id_; }
    const std::string& name() const { return name_; }

    std::string describe() const {
        return std::format("#{} {}", id_, name_);
    }

protected:
    // protected: invisible to the outside world, but available to classes
    // derived from Sensor. private members would not be.
    void log(const std::string& message) const {
        std::println("  [{}] {}", name_, message);
    }

private:
    int id_;
    std::string name_;
};

// A DERIVED class: "a TemperatureSensor IS A Sensor". The ": public Sensor"
// says so. It gets every public and protected member of Sensor for free, and
// adds its own.
class TemperatureSensor : public Sensor {
public:
    // The base class part must be built first, so the derived constructor
    // calls the base constructor in its initializer list. If it did not, the
    // compiler would look for a Sensor() default constructor, and fail.
    TemperatureSensor(int id, const std::string& name, double offset)
        : Sensor{id, name}, offset_{offset} {
        std::println("  TemperatureSensor constructed (offset {})", offset_);
    }

    ~TemperatureSensor() {
        std::println("  TemperatureSensor destroyed");
    }

    double calibrated(double raw) const {
        log("calibrating a reading");              // protected base member: allowed here
        return raw + offset_;
    }

    // Not allowed: id_ is PRIVATE to Sensor, so derived classes cannot see it.
    //     int broken() const { return id_; }      // error: 'id_' is private
    // Go through the public interface instead:
    std::string tag() const { return "T" + std::to_string(id()); }

private:
    double offset_;
};

// A derived class that adds nothing can inherit the base constructors as they
// are, with a using declaration.
class HumiditySensor : public Sensor {
public:
    using Sensor::Sensor;
};

int main() {

    std::println("building a TemperatureSensor:");
    TemperatureSensor north{1, "north", 1.5};

    // Everything public from Sensor is available on the derived object.
    std::println("\nname() = {}, id() = {}, describe() = {}", north.name(), north.id(), north.describe());
    std::println("calibrated(70.0) = {}", north.calibrated(70.0));
    std::println("tag() = {}", north.tag());

    // A derived object IS a base object, so it converts to a reference or a
    // pointer to its base without a cast.
    const Sensor& as_sensor{north};
    std::println("\nviewed as a Sensor: {}", as_sensor.describe());

    // But the base does not know the derived extras. This does not compile:
    //     as_sensor.calibrated(70.0);              // error: Sensor has no 'calibrated'

    std::println("\nsizeof(Sensor) = {}, sizeof(TemperatureSensor) = {}",
                 sizeof(Sensor), sizeof(TemperatureSensor));

    std::println("\nthe constructor-inheriting HumiditySensor:");
    HumiditySensor humidity{2, "east"};

    std::println("\nend of main, destruction in reverse order:");
    return 0;
}
