#include <format>
#include <memory>
#include <print>
#include <string>
#include <vector>

// An INTERFACE: a class with nothing but pure virtual functions. It says what
// something can do, and nothing about how.
class Reportable {
public:
    virtual ~Reportable() = default;
    virtual std::string report() const = 0;
};

// An ABSTRACT class: it has at least one PURE virtual function. "= 0" means
// "no implementation here, every concrete derived class must supply one".
// You cannot create an object of an abstract class, only of a class that has
// filled in every pure virtual function.
class Instrument : public Reportable {
public:
    explicit Instrument(const std::string& name) : name_{name} {}

    virtual double read() const = 0;                       // pure
    virtual std::string unit() const = 0;                  // pure

    // A normal member that uses the pure ones: a TEMPLATE for the derived
    // classes. It is written once, and works for every instrument.
    std::string report() const override {
        return std::format("{}: {:.1f} {}", name_, read(), unit());
    }

    const std::string& name() const { return name_; }

private:
    std::string name_;
};

class Thermometer : public Instrument {
public:
    using Instrument::Instrument;
    double read() const override { return 21.5; }
    std::string unit() const override { return "C"; }
};

class Barometer : public Instrument {
public:
    using Instrument::Instrument;
    double read() const override { return 1013.2; }
    std::string unit() const override { return "hPa"; }
};

// Forgetting one pure virtual function leaves the class abstract too:
class Unfinished : public Instrument {
public:
    using Instrument::Instrument;
    double read() const override { return 0.0; }
    // unit() is missing
};

// A function written against the INTERFACE works with anything that can
// report, including things that have nothing to do with instruments.
void print_report(const Reportable& item) {
    std::println("  {}", item.report());
}

class DailySummary : public Reportable {
public:
    std::string report() const override { return "summary: all instruments nominal"; }
};

int main() {

    // Instrument instrument{"x"};              // error: Instrument is abstract
    // Unfinished unfinished{"x"};              // error: unit() is still pure in Unfinished

    Thermometer thermometer{"thermometer"};
    Barometer barometer{"barometer"};
    DailySummary summary;

    std::println("through the Reportable interface:");
    print_report(thermometer);
    print_report(barometer);
    print_report(summary);

    // An abstract base is exactly the right element type for a container of
    // different things that share a job.
    std::vector<std::unique_ptr<Instrument>> instruments;
    instruments.push_back(std::make_unique<Thermometer>("north"));
    instruments.push_back(std::make_unique<Barometer>("roof"));

    std::println("\nthrough a container of Instrument pointers:");
    for (const auto& instrument : instruments) {
        std::println("  {}", instrument->report());
    }

    // The design idea: code that USES instruments depends only on Instrument.
    // A new kind (an Anemometer) means writing one new class and changing no
    // existing code.
    return 0;
}
