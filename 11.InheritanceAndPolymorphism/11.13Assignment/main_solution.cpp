#include <algorithm>
#include <format>
#include <memory>
#include <print>
#include <string>
#include <variant>
#include <vector>

/*
    Chapter 11 assignment - solutions
*/

// Provided classes for exercise 7.
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual std::string label() const { return "sensor"; }
};

class Thermometer : public Sensor {
public:
    std::string label() const override { return "thermometer"; }
};

class Anemometer : public Sensor {
public:
    explicit Anemometer(double gust) : gust_{gust} {}
    std::string label() const override { return "anemometer"; }
    double gust() const { return gust_; }

private:
    double gust_;
};

// ---------------------------------------------------------------------
// Exercise 1 - construction and destruction order
//
// The base part is built first (the derived constructor calls it in its
// initializer list) and destroyed last: the same last-in, first-out rule as
// in 10.6, applied to the layers of one object.
// ---------------------------------------------------------------------
class Instrument {
public:
    explicit Instrument(const std::string& name)
        : name_{name} {
        std::println("  Instrument {} built", name_);
    }

    ~Instrument() {
        std::println("  Instrument {} destroyed", name_);
    }

private:
    std::string name_;
};

class Barometer : public Instrument {
public:
    explicit Barometer(const std::string& name)
        : Instrument{name} {
        std::println("  Barometer built");
    }

    ~Barometer() {
        std::println("  Barometer destroyed");
    }
};

// ---------------------------------------------------------------------
// Exercises 2, 3 and 6 - virtual functions, a container, slicing
// ---------------------------------------------------------------------
class Gauge {
public:
    virtual ~Gauge() = default;
    virtual double read() const { return 0.0; }
    virtual std::string unit() const { return "units"; }
};

class Thermometer2 : public Gauge {
public:
    double read() const override { return 21.5; }
    std::string unit() const override { return "C"; }
};

class Barometer2 : public Gauge {
public:
    double read() const override { return 1013.2; }
    std::string unit() const override { return "hPa"; }
};

// Knows only about Gauge, takes a REFERENCE (never a Gauge by value, which
// would slice), and still prints each object's own values.
void show(const Gauge& gauge) {
    std::println("{} {}", gauge.read(), gauge.unit());
}

// ---------------------------------------------------------------------
// Exercise 4 - an abstract class
// ---------------------------------------------------------------------
class Alarm {
public:
    explicit Alarm(const std::string& name)
        : name_{name} {}

    virtual ~Alarm() = default;

    virtual bool triggered(double value) const = 0;
    std::string name() const { return name_; }

private:
    std::string name_;
};

class HighAlarm : public Alarm {
public:
    HighAlarm(const std::string& name, double limit)
        : Alarm{name}, limit_{limit} {}

    bool triggered(double value) const override { return value > limit_; }

private:
    double limit_;
};

class LowAlarm : public Alarm {
public:
    LowAlarm(const std::string& name, double limit)
        : Alarm{name}, limit_{limit} {}

    bool triggered(double value) const override { return value < limit_; }

private:
    double limit_;
};

// ---------------------------------------------------------------------
// Exercise 5 - the virtual destructor
// ---------------------------------------------------------------------
class Base {
public:
    virtual ~Base() {
        std::println("~Base");
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        std::println("~Derived");
    }
};

// ---------------------------------------------------------------------
// Exercise 8 - variant
// ---------------------------------------------------------------------
using Value = std::variant<int, double, std::string>;

struct Describe {
    std::string operator()(int value) const { return std::format("integer {}", value); }
    std::string operator()(double value) const { return std::format("decimal {}", value); }
    std::string operator()(const std::string& value) const { return std::format("text '{}'", value); }
};

std::string describe(const Value& value) {
    return std::visit(Describe{}, value);
}

int main() {

    std::println("--- Exercise 1: construction order ---");
    {
        Barometer roof{"roof"};
    }

    std::println("\n--- Exercise 2: virtual and override ---");
    Thermometer2 thermometer;
    Barometer2 barometer;
    Gauge plain;
    show(thermometer);
    show(barometer);
    show(plain);

    std::println("\n--- Exercise 3: a polymorphic container ---");
    std::vector<std::unique_ptr<Gauge>> gauges;
    gauges.push_back(std::make_unique<Thermometer2>());
    gauges.push_back(std::make_unique<Thermometer2>());
    gauges.push_back(std::make_unique<Barometer2>());
    double total{0.0};
    for (const auto& gauge : gauges) {
        std::println("{}", gauge->unit());
        total += gauge->read();
    }
    std::println("total: {}", total);

    std::println("\n--- Exercise 4: an abstract class ---");
    std::vector<std::unique_ptr<Alarm>> alarms;
    alarms.push_back(std::make_unique<HighAlarm>("heat", 30.0));
    alarms.push_back(std::make_unique<LowAlarm>("frost", 0.0));
    for (const auto& alarm : alarms) {
        std::println("{}: {}", alarm->name(), alarm->triggered(35.0) ? "triggered" : "quiet");
    }

    std::println("\n--- Exercise 5: the virtual destructor ---");
    {
        std::unique_ptr<Base> owner{std::make_unique<Derived>()};
    }
    // Without "virtual", deleting a Derived through a Base pointer is
    // undefined behaviour: in practice only ~Base runs, ~Derived is skipped,
    // and anything Derived owns is leaked (AddressSanitizer reports it as a
    // new-delete-type-mismatch).

    std::println("\n--- Exercise 6: slicing ---");
    Thermometer2 original;
    Gauge sliced{original};
    const Gauge& referenced{original};
    std::println("sliced:     {}", sliced.unit());
    std::println("referenced: {}", referenced.unit());
    // Initializing a Gauge VALUE from a Thermometer2 copies only the Gauge
    // part, so the object is a plain Gauge and its virtual functions run the
    // Gauge versions. A reference refers to the real Thermometer2.

    std::println("\n--- Exercise 7: dynamic_cast ---");
    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.push_back(std::make_unique<Thermometer>());
    sensors.push_back(std::make_unique<Anemometer>(18.5));
    sensors.push_back(std::make_unique<Thermometer>());
    sensors.push_back(std::make_unique<Anemometer>(24.0));

    int anemometers{0};
    double largest_gust{0.0};
    for (const auto& sensor : sensors) {
        if (const auto* anemometer{dynamic_cast<const Anemometer*>(sensor.get())}) {
            ++anemometers;
            largest_gust = std::max(largest_gust, anemometer->gust());
        }
    }
    std::println("{} anemometers, largest gust {}", anemometers, largest_gust);

    std::println("\n--- Exercise 8: variant ---");
    std::vector<Value> values;
    values.push_back(7);
    values.push_back(2.5);
    values.push_back(std::string{"hail"});
    for (const Value& value : values) {
        std::println("{}", describe(value));
    }

    return 0;
}
