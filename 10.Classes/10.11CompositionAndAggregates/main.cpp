#include <cstddef>
#include <print>
#include <string>
#include <utility>
#include <vector>

// An AGGREGATE: a plain bundle of data with no constructors, no private
// members, no rules to protect. A struct is the right tool, and it can be
// initialized by listing the values.
struct Location {
    double latitude;
    double longitude;
};

enum class Status { online, offline, faulty };

std::string to_string(Status status) {
    switch (status) {
        case Status::online:  return "online";
        case Status::offline: return "offline";
        case Status::faulty:  return "faulty";
    }
    return "unknown";
}

// A part that announces when it is built and when it is destroyed, to make
// the order visible.
class Part {
public:
    explicit Part(std::string name)
        : name_{std::move(name)} {
        std::println("    {} built", name_);
    }

    ~Part() {
        std::println("    {} destroyed", name_);
    }

private:
    std::string name_;
};

// COMPOSITION: a Station is made OF other objects. It "has a" Location, "has a"
// Status, "has some" Sensors. Its members are built before its own constructor
// body runs, in the order they are declared, and destroyed in the opposite
// order after its destructor body.
class Station {
public:
    Station(std::string name, Location where)
        : name_{std::move(name)}, where_{where} {
        std::println("    Station {} constructor body runs", name_);
    }

    ~Station() {
        std::println("    Station {} destructor body runs", name_);
    }

    void add_sensor(const std::string& sensor_name) {
        sensors_.push_back(sensor_name);
    }

    void set_status(Status status) { status_ = status; }

    void print() const {
        std::println("  {} at ({}, {}), {}, {} sensor(s)",
                     name_, where_.latitude, where_.longitude,
                     to_string(status_), sensors_.size());
    }

private:
    std::string name_;
    Location where_;
    Status status_{Status::online};
    std::vector<std::string> sensors_;
    Part antenna_{"antenna"};
    Part battery_{"battery"};
};

int main() {

    // Aggregate initialization: values in declaration order.
    Location seattle{47.6, -122.3};

    // Designated initializers (C++20): name the fields. The names must come
    // in declaration order, and a reader never has to guess which number is
    // the latitude.
    Location denver{.latitude = 39.7, .longitude = -105.0};

    // A structured binding (C++17) unpacks an aggregate into named variables,
    // in declaration order: lat is denver.latitude, lon is denver.longitude.
    auto [lat, lon]{denver};
    std::println("denver: latitude {}, longitude {}", lat, lon);

    std::println("\nbuilding a station:");
    {
        Station station{"Rooftop", seattle};
        std::println("  --- constructed, now using it ---");
        station.add_sensor("north");
        station.add_sensor("east");
        station.set_status(Status::faulty);
        station.print();
        std::println("  --- leaving the scope ---");
    }

    // The order above is the point. Reading it top to bottom:
    //   1. the members are built in DECLARATION order (name_, where_, status_,
    //      sensors_, antenna_, battery_)
    //   2. only then does the constructor body run
    //   3. on the way out, the destructor body runs FIRST
    //   4. then the members are destroyed in REVERSE order: battery before antenna
    //
    // Struct or class? A struct for plain data that cannot be wrong
    // (Location). A class when there are rules to keep (Station).
    return 0;
}
