#include <format>
#include <print>
#include <string>
#include <variant>
#include <vector>

// The inheritance way (11.3 to 11.5) is OPEN: anyone can add a new derived
// class later, and code written against the base keeps working. The price is a
// pointer, a heap allocation per object, and a virtual call.
//
// When the set of kinds is CLOSED, known and fixed, there is another way: a
// std::variant, a value that holds exactly one of a listed set of types. No
// base class, no pointers, no heap, all values stored inline.

struct Temperature {
    double celsius;
    std::string describe() const { return std::format("{:.1f} C", celsius); }
};

struct Humidity {
    double percent;
    std::string describe() const { return std::format("{:.0f} % humidity", percent); }
};

struct Wind {
    double speed;
    double heading;
    std::string describe() const { return std::format("{} km/h at {} degrees", speed, heading); }
};

// A reading is a Temperature OR a Humidity OR a Wind.
using Reading = std::variant<Temperature, Humidity, Wind>;

// A visitor: one operator() per alternative. std::visit calls the one that
// matches whatever the variant holds right now. (operator() is chapter 12.)
// Leave an alternative out and the program does not compile: the compiler
// checks that every case is handled.
struct Summarize {
    std::string operator()(const Temperature& t) const { return std::format("it is {:.1f} degrees", t.celsius); }
    std::string operator()(const Humidity& h) const { return std::format("the air is {:.0f} % wet", h.percent); }
    std::string operator()(const Wind& w) const { return std::format("wind of {} km/h", w.speed); }
};

int main() {

    std::vector<Reading> readings;
    readings.push_back(Temperature{21.5});
    readings.push_back(Humidity{63.0});
    readings.push_back(Wind{12.0, 270.0});
    readings.push_back(Temperature{19.0});

    // 1. A generic lambda with an auto parameter: when every alternative has
    //    the same member function, one lambda serves them all.
    std::println("describe(), through a generic lambda:");
    for (const Reading& reading : readings) {
        std::println("  {}", std::visit([](const auto& value) { return value.describe(); }, reading));
    }

    // 2. A visitor with one case per type, for when each one needs different code.
    std::println("\nSummarize, one case per type:");
    for (const Reading& reading : readings) {
        std::println("  {}", std::visit(Summarize{}, reading));
    }

    // 3. Asking directly what a variant holds right now.
    const Reading& first{readings[0]};
    std::println("\nfirst holds a Temperature: {}", std::holds_alternative<Temperature>(first));
    std::println("first holds a Wind:        {}", std::holds_alternative<Wind>(first));
    std::println("index of the active type:  {}", first.index());       // 0 for Temperature, 1 Humidity, 2 Wind

    // get_if returns a pointer to the value if that is the active type, or
    // nullptr if not. The same shape as dynamic_cast, but checked against a
    // closed list of types, with no virtual function and no heap.
    if (const auto* wind{std::get_if<Wind>(&readings[2])}) {
        std::println("readings[2] is a Wind: speed {}", wind->speed);
    }
    if (std::get_if<Wind>(&readings[0]) == nullptr) {
        std::println("readings[0] is not a Wind");
    }

    // std::get<T> returns the value, but throws std::bad_variant_access if T
    // is not the active alternative (chapter 13). Prefer get_if or visit.

    std::println("\nsizeof(Reading) = {}  (room for the largest alternative, plus a tag)", sizeof(Reading));

    // Which one to choose?
    //   inheritance   open set of types, behaviour varies per type, objects may be large
    //   variant       closed set of types, values stored inline, new OPERATIONS are easy
    // With a variant, adding a new OPERATION is one new visitor. Adding a new
    // TYPE means changing the list and every visitor. With inheritance it is
    // exactly the other way round.
    return 0;
}
