#include <print>
#include <string>

class Sensor {
public:
    // A static CONSTANT: one value, shared by the whole class, usable at
    // compile time. Nothing is stored per object.
    static constexpr double max_offset{5.0};

    explicit Sensor(const std::string& name)
        : name_{name} {
        ++active_;
        ++created_;
    }

    // A static member variable lives once, outside every object. "inline"
    // lets it be defined right here in the class (C++17), instead of in a .cpp.
    // It counts how many Sensors exist right now, so the destructor
    // must give back what the constructor took.
    ~Sensor() {
        --active_;
    }

    // Gotcha: the compiler writes a copy constructor that copies the members
    // and does NOTHING ELSE, so the count would miss every copy. Writing our
    // own one fixes it. Comment these two lines out and watch the count in
    // main become wrong.
    Sensor(const Sensor& other)
        : name_{other.name_}, offset_{other.offset_} {
        ++active_;
        ++created_;
    }

    // A static member FUNCTION belongs to the class, not to an object. It has
    // no "this", so it can only touch static members. Call it with the class
    // name: Sensor::active().
    static int active() { return active_; }
    static int created() { return created_; }

    // "this" is a pointer to the object the function was called on. Returning
    // *this (the object itself, by reference) lets calls be chained:
    //     sensor.rename("x").set_offset(1.0);
    Sensor& rename(const std::string& name) {
        name_ = name;
        return *this;
    }

    Sensor& set_offset(double offset) {
        if (offset >= -max_offset && offset <= max_offset) {
            offset_ = offset;
        }
        return *this;
    }

    // A friend is a non-member function that is allowed to see the private
    // parts. It is not a member: it is declared here, to grant the access,
    // and defined outside.
    friend void print_debug(const Sensor& sensor);

    const std::string& name() const { return name_; }

private:
    std::string name_;
    double offset_{0.0};

    static inline int active_{0};
    static inline int created_{0};
};

void print_debug(const Sensor& sensor) {
    // Reaches name_ and offset_ directly, which a normal function could not.
    std::println("  debug: name_='{}' offset_={}", sensor.name_, sensor.offset_);
}

int main() {

    std::println("max_offset = {} (no object needed)", Sensor::max_offset);
    std::println("sensors alive at the start: {}", Sensor::active());

    Sensor north{"north"};
    Sensor east{"east"};
    std::println("after creating two: {}", Sensor::active());

    {
        Sensor copy{north};
        std::println("inside a scope, with a copy: {} alive ({} ever created)",
                     Sensor::active(), Sensor::created());
    }
    std::println("after the scope: {} alive ({} ever created)",
                 Sensor::active(), Sensor::created());

    std::println("\nchained setters, using *this:");
    north.rename("north-2").set_offset(1.5).set_offset(99.0);
    print_debug(north);

    // A static function can also be called through an object, but that hides
    // the fact that no object is involved. Prefer the class name.
    std::println("\nvia an object (works, but misleading): {}", north.active());
    return 0;
}
