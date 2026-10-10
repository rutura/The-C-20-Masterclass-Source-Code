#include <print>

class Fahrenheit;

class Celsius {
public:
    // A one-argument constructor is also a CONVERSION: from double to Celsius.
    // "explicit" makes it happen only when you write it out.
    explicit Celsius(double degrees) : degrees_{degrees} {}

    double degrees() const { return degrees_; }

    // A CONVERSION OPERATOR goes the other way: from this class to another
    // type. "operator Fahrenheit()" has no return type written: the type IS
    // the name. Declared here, defined below, once Fahrenheit is complete.
    explicit operator Fahrenheit() const;

private:
    double degrees_;
};

class Fahrenheit {
public:
    explicit Fahrenheit(double degrees) : degrees_{degrees} {}
    double degrees() const { return degrees_; }

private:
    double degrees_;
};

Celsius::operator Fahrenheit() const {
    return Fahrenheit{degrees_ * 9.0 / 5.0 + 32.0};
}

// A value that may or may not be there.
class MaybeReading {
public:
    MaybeReading() = default;
    explicit MaybeReading(double value) : value_{value}, valid_{true} {}

    // "explicit operator bool" is the standard way to make an object usable in
    // a condition, as pointers and smart pointers are (9.2, 9.10):
    //     if (reading) { ... }
    // It is used in conditions (if, while, !, &&, ||) automatically, and
    // nowhere else, so a MaybeReading never turns into the number 1 by accident.
    explicit operator bool() const { return valid_; }

    double value() const { return value_; }

private:
    double value_{0.0};
    bool valid_{false};
};

// The cautionary tale: the SAME classes with IMPLICIT conversions. A
// constructor without "explicit" lets the compiler convert on its own.
class LooseMeters {
public:
    LooseMeters(double meters) : meters_{meters} {}       // NOT explicit
    double meters() const { return meters_; }

private:
    double meters_;
};

void print_length(LooseMeters length) {
    std::println("  length: {} m", length.meters());
}

void print_temperature(Celsius temperature) {
    std::println("  temperature: {} C", temperature.degrees());
}

int main() {

    Celsius freezing{0.0};

    // With explicit, the conversion has to be asked for, with static_cast...
    Fahrenheit f{static_cast<Fahrenheit>(freezing)};
    std::println("0 C is {} F", f.degrees());

    // ...and a bare number can NOT silently become a Celsius:
    //     print_temperature(21.5);               // error: no implicit conversion from double
    print_temperature(Celsius{21.5});             // you must say what you mean
    //     Fahrenheit g{freezing};                // error: also not implicit

    std::println("\nthe explicit operator bool:");
    MaybeReading nothing;
    MaybeReading something{21.5};

    if (something) {
        std::println("  something holds {}", something.value());
    }
    if (!nothing) {
        std::println("  nothing holds nothing");
    }
    //     double oops{something};                // error: bool conversion is explicit, and not to double anyway
    //     int count{nothing + something};        // error: no arithmetic on a MaybeReading

    std::println("\nthe implicit constructor, for comparison:");
    print_length(LooseMeters{5.0});
    print_length(5.0);          // compiles: a plain number silently becomes a LooseMeters
    print_length(true);         // compiles too: a bool becomes 1.0 meter. Almost never intended.

    // The rule: mark every one-argument constructor, and every conversion
    // operator, explicit, unless you can say why you want the silent
    // conversion. (std::string from a literal and std::vector from nothing are
    // the kind of case where implicit is right: a text literal IS a string.)
    return 0;
}
