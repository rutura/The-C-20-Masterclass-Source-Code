#include <print>
#include <string>

// ---------------------------------------------------------------------------
// Multiple inheritance with INTERFACES: the safe and common use.
// A class can be several things at once.
// ---------------------------------------------------------------------------
class Reportable {
public:
    virtual ~Reportable() = default;
    virtual std::string report() const = 0;
};

class Rechargeable {
public:
    virtual ~Rechargeable() = default;
    virtual int battery_percent() const = 0;
};

class SolarSensor : public Reportable, public Rechargeable {
public:
    std::string report() const override { return "solar sensor: ok"; }
    int battery_percent() const override { return 87; }
};

void print_report(const Reportable& item) {
    std::println("  {}", item.report());
}

void print_battery(const Rechargeable& item) {
    std::println("  battery {}%", item.battery_percent());
}

// ---------------------------------------------------------------------------
// Multiple inheritance with DATA in the base: the diamond problem.
// ---------------------------------------------------------------------------
int devices_built{0};

struct Device {
    explicit Device(int serial) : serial_number{serial} {
        ++devices_built;
    }
    int serial_number;
};

// Station inherits from Radio and from Meter, and both of those inherit from
// Device: two paths to the same base, which is why this is called a diamond.
//
//              Device
//             /      |
//        Radio        Meter
//             |      /
//             Station
struct Radio : Device {
    Radio() : Device{1} {}
};

struct Meter : Device {
    Meter() : Device{2} {}
};

struct Station : Radio, Meter {};           // contains TWO Device parts, one per path

// ---------------------------------------------------------------------------
// The fix: virtual inheritance. The shared base is built ONCE, and the
// most-derived class is the one that constructs it.
// ---------------------------------------------------------------------------
struct VRadio : virtual Device {
    VRadio() : Device{1} {}                 // ignored when VRadio is part of something bigger
};

struct VMeter : virtual Device {
    VMeter() : Device{2} {}                 // ignored too
};

struct VStation : VRadio, VMeter {
    VStation() : Device{99} {}              // the most-derived class builds the one Device
};

int main() {

    std::println("one class implementing two interfaces:");
    SolarSensor solar;
    print_report(solar);
    print_battery(solar);

    std::println("\nthe diamond, plain inheritance:");
    devices_built = 0;
    Station station;
    std::println("  Device parts built: {}", devices_built);
    std::println("  sizeof(Station) = {}", sizeof(Station));
    // station.serial_number;                // error: ambiguous, Radio's or Meter's?
    std::println("  Radio's serial: {}, Meter's serial: {}",
                 station.Radio::serial_number, station.Meter::serial_number);

    std::println("\nthe diamond, virtual inheritance:");
    devices_built = 0;
    VStation virtual_station;
    std::println("  Device parts built: {}", devices_built);
    std::println("  sizeof(VStation) = {}", sizeof(VStation));
    std::println("  the one serial number: {}", virtual_station.serial_number);

    // Interfaces with no data are always safe to combine. A diamond of
    // classes WITH data is a sign to rethink: prefer one base class plus
    // interfaces, or composition (11.8).
    return 0;
}
