#include <print>
#include <string>

// A helper that announces itself, so that you can SEE the order in which
// members are initialized.
struct Noisy {
    explicit Noisy(const char* label) {
        std::println("    initializing {}", label);
    }
};

class Sensor {
public:
    // The main constructor. Everything after the colon is the MEMBER
    // INITIALIZER LIST: it builds each member directly with the value given.
    // Without it, a member would first be default-constructed and then
    // assigned, which is wasteful, and for some members impossible.
    Sensor(int id, const std::string& name, double offset)
        : id_{id}, name_{name}, offset_{offset} {
        std::println("  Sensor {} ({}) created, offset {}", id_, name_, offset_);
    }

    // A delegating constructor hands the work to another one, so that the
    // setup logic is written only once.
    Sensor(int id, const std::string& name)
        : Sensor{id, name, 0.0} {}

    // "explicit" stops the compiler from using this constructor for silent
    // conversions. Without it, a bare int could turn into a Sensor by itself.
    explicit Sensor(int id)
        : Sensor{id, "unnamed"} {}

    // Asking the compiler to write the default constructor, using the default
    // member initializers below.
    Sensor() = default;

    int id() const { return id_; }
    const std::string& name() const { return name_; }
    double offset() const { return offset_; }

private:
    // A const member can only be set in the initializer list, never assigned.
    // The same goes for a reference member.
    const int id_{0};
    std::string name_{"unnamed"};
    double offset_{0.0};
};

// Members are initialized in the order they are DECLARED in the class, not in
// the order they appear in the initializer list. Run this and look at the
// output: "second_" is listed first below and still comes second. Compilers
// warn about a list that disagrees with the declaration order (-Wreorder on
// GCC and Clang), and the warning is worth listening to.
class Pair {
public:
    Pair() : second_{"second_"}, first_{"first_"} {}

private:
    Noisy first_;
    Noisy second_;
};

void describe(const Sensor& sensor) {
    std::println("  {} / {} / {}", sensor.id(), sensor.name(), sensor.offset());
}

int main() {

    std::println("full constructor:");
    Sensor north{12, "north", 1.5};

    std::println("\ndelegating to the full one:");
    Sensor east{13, "east"};

    std::println("\nthe one-argument constructor:");
    Sensor unnamed{14};

    std::println("\ndefault constructor (compiler-written, uses the member defaults):");
    Sensor blank;
    describe(blank);

    // Because of "explicit", this is refused:
    //     Sensor accidental = 15;          // error: cannot convert int to Sensor
    //     describe(15);                    // error, for the same reason
    // Without it, both would quietly build a Sensor from the number 15.

    std::println("\nmember initialization order:");
    Pair pair;

    // Brace initialization also refuses narrowing, which parentheses allow:
    //     Sensor lossy{12.7, "x", 0.0};    // error: double to int would lose data
    return 0;
}
