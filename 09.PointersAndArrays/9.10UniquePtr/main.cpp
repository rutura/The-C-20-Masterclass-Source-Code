#include <cstddef>
#include <memory>
#include <print>
#include <string>
#include <utility>

struct Probe {
    std::string name;

    ~Probe() {
        std::println("  probe {} shut down", name);
    }
};

// Returning a unique_ptr hands the new object, and the duty to clean it up,
// to the caller. Nothing is copied.
std::unique_ptr<Probe> make_probe(const std::string& name) {
    return std::make_unique<Probe>(name);
}

// Takes a plain reference: it only LOOKS at the probe and owns nothing. This
// is the right parameter type for most functions, and it works with any kind
// of smart pointer, or no pointer at all.
void inspect(const Probe& probe) {
    std::println("  inspecting {}", probe.name);
}

// Takes a unique_ptr BY VALUE: the function becomes the new owner and the
// probe is destroyed when this function ends, unless it passes it on.
void retire(std::unique_ptr<Probe> probe) {
    std::println("  retiring {}", probe->name);
}

int main() {

    // A unique_ptr owns exactly one object and deletes it when the
    // unique_ptr itself dies. make_unique is the way to create one.
    {
        auto probe{std::make_unique<Probe>("north")};
        std::println("using {}", probe->name);      // -> and * work like a raw pointer
        std::println("(*probe).name = {}", (*probe).name);
    }   // no delete anywhere: the destructor message appears right here
    std::println("scope ended\n");

    // Exactly one owner at any time, so copying is not allowed. This line
    // would not compile:
    //     auto copy{probe};
    // Ownership can only be MOVED. std::move says "I am done with this one,
    // give it away". Chapter 10 explains what a move really is.
    auto first_owner{make_probe("east")};
    auto second_owner{std::move(first_owner)};
    std::println("first_owner is empty: {}", first_owner == nullptr);
    std::println("second_owner has: {}\n", second_owner->name);

    // Lending and giving away.
    inspect(*second_owner);            // lend: the function sees it, we keep it
    retire(std::move(second_owner));   // give away: it is destroyed inside retire
    std::println("back in main, second_owner is empty: {}\n", second_owner == nullptr);

    // Arrays: the [] form of unique_ptr calls delete[] for you.
    std::size_t count{5};
    auto readings{std::make_unique<int[]>(count)};     // all elements start at 0
    for (std::size_t i{0}; i < count; ++i) {
        readings[i] = 68 + static_cast<int>(i);
    }
    std::println("readings[4] = {}", readings[4]);

    // get() returns the raw pointer, for an old API that wants one. It stays
    // owned by the unique_ptr: never delete it yourself, never store it
    // beyond the owner's life.
    int* raw{readings.get()};
    std::println("raw[0] = {}", raw[0]);

    // reset() destroys the current object now. With an argument it takes a
    // new one.
    auto temporary{make_probe("south")};
    std::println("\nresetting temporary:");
    temporary.reset();
    std::println("temporary is empty: {}", temporary == nullptr);

    std::println("\nend of main");
    return 0;
}
