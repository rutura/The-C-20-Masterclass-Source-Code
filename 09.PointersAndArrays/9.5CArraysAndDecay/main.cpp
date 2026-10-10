#include <array>
#include <cstddef>
#include <iterator>
#include <print>

// What the compiler really sees here is "int* values". The 5 between the
// brackets is ignored, and so is any other number. The array was never passed:
// only the address of its first element was. GCC and Clang warn about the
// sizeof line below, which is exactly the point.
void inside_the_function(int values[5]) {
    std::println("inside:  sizeof(values) = {}  (the size of a pointer, not of 5 ints)",
                 sizeof(values));
}

// The honest signature: an address, plus a count carried separately.
void print_all(const int* values, std::size_t count) {
    for (std::size_t i{0}; i < count; ++i) {
        std::print("{} ", values[i]);
    }
    std::println("");
}

int main() {

    // A built-in array: a fixed number of values, side by side in memory.
    int readings[5]{68, 71, 69, 72, 70};

    // In the scope where the array is declared, the compiler knows its size.
    std::println("sizeof(readings)    = {}", sizeof(readings));
    std::println("sizeof(readings[0]) = {}", sizeof(readings[0]));
    std::println("element count (old idiom) = {}", sizeof(readings) / sizeof(readings[0]));
    std::println("element count (std::size) = {}", std::size(readings));

    // Range-based for works on a true array, because the size is known here.
    std::print("range-for: ");
    for (int reading : readings) {
        std::print("{} ", reading);
    }
    std::println("");

    // Decay: in almost every expression the array name turns into a pointer
    // to its first element. The size does not travel with it.
    int* first{readings};
    std::println("\nreadings == &readings[0]: {}", readings == &readings[0]);
    std::println("first[2] = {}", first[2]);

    std::println("\noutside: sizeof(readings) = {}", sizeof(readings));
    inside_the_function(readings);

    // The pointer-and-count pair is how C code passes arrays. It works, but
    // nothing checks that the count is right.
    print_all(readings, std::size(readings));

    // Limits of a built-in array, none of them reported by the compiler:
    //   int copy[5]{};  copy = readings;     does not compile: arrays cannot be assigned
    //   readings[5] = 0;                      compiles, undefined behaviour: one past the end
    //   readings[-1]                          compiles, undefined behaviour: before the start
    // The program above will not warn you, and may appear to work.

    // The std::array from 7.2 has none of these problems: it copies, it knows
    // its size, and at() checks the index. std::to_array turns a built-in
    // array into one.
    auto modern{std::to_array(readings)};
    auto copy{modern};
    copy[0] = 0;
    std::println("\nmodern.size() = {}, modern[0] = {}, copy[0] = {}",
                 modern.size(), modern[0], copy[0]);

    return 0;
}
