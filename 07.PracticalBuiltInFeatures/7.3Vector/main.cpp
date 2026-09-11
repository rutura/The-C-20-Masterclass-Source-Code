#include <print>
#include <stdexcept>
#include <vector>

void printReadings(const std::vector<int>& readings) {
    for (const int& reading : readings) {
        std::print("{} ", reading);
    }
    std::println("");
}

int main() {

    // std::vector<T> - like std::array, but its size can change at run
    // time and its elements live on the heap. vector(7) makes 7 elements,
    // each value-initialized to 0.
    std::vector<int> morningReadings(7);
    std::vector<int> eveningReadings(10);

    std::println("Size of morningReadings is {}", morningReadings.size());
    printReadings(morningReadings);

    std::println("Size of eveningReadings is {}", eveningReadings.size());
    printReadings(eveningReadings);

    // Two vectors compare element by element, like std::array.
    if (morningReadings != eveningReadings) {
        std::println("morningReadings and eveningReadings are not equal "
                      "(different sizes)");
    }

    // Copy constructor: afternoonReadings starts as an independent copy.
    std::vector afternoonReadings{morningReadings};
    std::println("\nSize of afternoonReadings is {}", afternoonReadings.size());

    // Assignment replaces morningReadings' contents with eveningReadings'.
    morningReadings = eveningReadings;
    std::println("\nAfter assigning eveningReadings to morningReadings:");
    std::println("morningReadings and eveningReadings are equal: {}",
                  morningReadings == eveningReadings);

    // .at(i) as an lvalue: bounds-checked write.
    morningReadings.at(5) = 1000;
    std::print("morningReadings: ");
    printReadings(morningReadings);

    // Out-of-range access throws std::out_of_range - catch it instead of
    // crashing.
    try {
        std::println("\nAttempting morningReadings.at(15)");
        std::println("{}", morningReadings.at(15));
    }
    catch (const std::out_of_range& ex) {
        std::println("An exception occurred: {}", ex.what());
    }

    // A vector can grow. push_back appends one element, resizing as
    // needed - this is what std::array cannot do.
    std::println("\nCurrent afternoonReadings size is {}", afternoonReadings.size());
    afternoonReadings.push_back(1000);
    std::println("New afternoonReadings size is {}", afternoonReadings.size());
    std::print("afternoonReadings now contains: ");
    printReadings(afternoonReadings);

    return 0;
}
