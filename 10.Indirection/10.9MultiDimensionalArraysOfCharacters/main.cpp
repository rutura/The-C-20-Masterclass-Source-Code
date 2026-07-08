#include <print>

int main() {

    const size_t name_length{15};

    char members[][name_length]{
        {'J', 'o', 'h', 'n'},
        {'S', 'a', 'm', 'u', 'e', 'l'},
        {'R', 'a', 's', 'h', 'i', 'd'},
        {'R', 'o', 'd', 'r', 'i', 'g', 'e', 'z'}};

    // Printing like this is unsafe: without a null terminator, it keeps
    // reading past the array's own memory until it happens to hit a zero
    // byte somewhere else.
    /*
    std::println("Unsafe printing of members : ");
    for (size_t i{0}; i < std::size(members); ++i) {
        std::println("{}", members[i]);
    }
    */

    // Looping character by character avoids that risk entirely, but it's
    // more code than it needs to be.
    /*
    std::println("");
    std::println("Printing out character by character manually : ");
    for (size_t i{0}; i < std::size(members); ++i) {
        for (size_t j{0}; j < std::size(members[i]); ++j) {
            std::print("{}", members[i][j]);
        }
        std::println("");
    }
    */

    // Better: C-string literals. The compiler adds the null terminator for
    // each row, so printing the whole row directly is safe again.
    /*
    char members1[][name_length]{
        "John",
        "Samuel",
        "Rashid",
        "Rodriguez"};

    std::println("Printing out members1 (C-string literals) : ");
    for (size_t i{0}; i < std::size(members1); ++i) {
        std::println("{}", members1[i]);
    }
    */

    // Updating the fortune teller's predictions the same way
    char predictions[][90]{
        "a lot of kinds running in the backyard!",
        "a lot of empty beer bootles on your work table.",
        "you Partying too much with kids wearing weird clothes.",
        "you running away from something really scary",
        "clouds gathering in the sky and an army standing ready for war",
        "dogs running around in a deserted empty city",
        "a lot of cars stuck in a terrible traffic jam",
        "you sitting in the dark typing lots of lines of code on your dirty computer",
        "you yelling at your boss. And oh no! You get fired!",
        "you laughing your lungs out. I've never seen this before.",
        "Uhm, I don't see anything!"};

    std::println("");
    std::println("Prediction : {}", predictions[5]);

    return 0;
}
