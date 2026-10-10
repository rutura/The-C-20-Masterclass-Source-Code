#include <cstddef>
#include <print>
#include <string>
#include <vector>

class Sensor {
public:
    explicit Sensor(const std::string& name)
        : name_{name} {}

    // Non-const: changes the object, so it cannot be called on a const Sensor.
    void record(double reading) {
        readings_.push_back(reading);
    }

    // Const: promises not to change the object. The "const" after the
    // parameter list is part of the function's type, and the compiler checks
    // the promise: assigning to a member inside this function would not compile.
    std::size_t count() const {
        return readings_.size();
    }

    double latest() const {
        return readings_.empty() ? 0.0 : readings_.back();
    }

    // A const function may still need to update a private bookkeeping value
    // that is not part of the sensor's "real" state. "mutable" marks such a
    // member as exempt. Use it sparingly: only for caches and counters.
    double average() const {
        ++average_calls_;
        double total{0.0};
        for (double reading : readings_) {
            total += reading;
        }
        return readings_.empty() ? 0.0 : total / static_cast<double>(readings_.size());
    }

    std::size_t average_calls() const {
        return average_calls_;
    }

    // Two overloads that differ only by const: a read-only view for const
    // objects, a writable one for the rest. The returned reference follows the
    // same rule as the function.
    const std::vector<double>& readings() const {
        return readings_;
    }

    std::vector<double>& readings() {
        return readings_;
    }

    const std::string& name() const {
        return name_;
    }

private:
    std::string name_;
    std::vector<double> readings_;
    mutable std::size_t average_calls_{0};
};

// A const reference parameter (7.3) only lets us call const member functions.
// That is why const-correct classes mark every function that only looks.
void report(const Sensor& sensor) {
    std::println("{}: {} readings, latest {}, average {:.1f}",
                 sensor.name(), sensor.count(), sensor.latest(), sensor.average());

    // sensor.record(1.0);      // error: 'record' is not const, but sensor is
}

int main() {

    Sensor north{"north"};
    north.record(68.0);
    north.record(71.5);
    north.record(70.0);
    report(north);

    // A const object can be built, read, and nothing else.
    const Sensor archived{"archived"};
    std::println("\n{} has {} readings", archived.name(), archived.count());
    // archived.record(65.0);   // error: cannot call a non-const function on a const object

    // mutable at work: average() is const, yet it counted its own calls.
    north.average();
    north.average();
    std::println("\nnorth.average() has been called {} times", north.average_calls());

    // The overload pair: a non-const sensor hands out a writable vector...
    north.readings().push_back(72.0);
    std::println("after pushing through readings(): {} readings", north.count());

    // ...and a const one hands out a read-only view.
    const std::vector<double>& view{archived.readings()};
    std::println("archived view has {} elements", view.size());
    // archived.readings().push_back(1.0);   // error: the returned vector is const

    return 0;
}
