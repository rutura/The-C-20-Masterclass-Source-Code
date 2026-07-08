#include <print>

int main() {

    int numbers[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    // Reading beyond bounds: will read garbage, or crash your program.
    // std::println("numbers[12] : {}", numbers[12]);

    // Writing beyond bounds is just as unchecked - the compiler allows it,
    // but index 129 isn't memory this array owns. It might belong to
    // another variable, or to nothing valid at all: writing there can
    // silently corrupt unrelated data, or crash immediately, or appear to
    // "work" while quietly breaking something else entirely. Left
    // commented out rather than executed, since which of those happens is
    // unpredictable by design - that unpredictability is the whole danger.
    // numbers[129] = 1000;
    // std::println("numbers[129] : {}", numbers[129]);

    std::println("Program ending....");

    return 0;
}
