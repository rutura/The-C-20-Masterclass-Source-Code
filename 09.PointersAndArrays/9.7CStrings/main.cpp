#include <cstddef>
#include <cstdio>
#include <cstring>
#include <print>
#include <string>
#include <string_view>

// What std::strlen does: walk until the terminating '\0' (the character with
// the numeric value 0). A C string has no stored length. The terminator IS
// the length information.
std::size_t my_strlen(const char* text) {
    const char* p{text};
    while (*p != '\0') {
        ++p;
    }
    return static_cast<std::size_t>(p - text);
}

// argc is the number of command-line arguments, argv an array of C strings.
// argv[0] is the program itself, so argc is at least 1.
int main(int argc, char* argv[]) {

    // A string literal is a built-in array of const char, ending in '\0'.
    // "sensor-12" has 9 letters, so the array has 10 elements.
    const char* label{"sensor-12"};
    std::println("sizeof(\"sensor-12\") = {}", sizeof("sensor-12"));
    std::println("std::strlen(label)  = {}", std::strlen(label));
    std::println("my_strlen(label)    = {}", my_strlen(label));

    // Print the first few characters as numbers: the last one is 0.
    std::print("last four bytes: ");
    for (std::size_t i{6}; i <= 9; ++i) {
        std::print("{} ", static_cast<int>(label[i]));
    }
    std::println("");

    // To get text you can modify, copy it into a char array. The size must
    // include room for the terminator, and the unused part is set to zero.
    char editable[16]{"sensor-12"};
    editable[7] = '4';
    editable[8] = '2';
    std::println("\neditable = {}", editable);

    // Gotcha: == on two char pointers compares ADDRESSES, not letters. These
    // two arrays hold the same text, at two different places in memory.
    char twin[16]{"sensor-12"};
    char other_twin[16]{"sensor-12"};
    const char* twin_address{twin};
    const char* other_twin_address{other_twin};
    std::println("\nsame text, same address?  {}", twin_address == other_twin_address);
    std::println("strcmp(twin, other) == 0: {}", std::strcmp(twin, other_twin) == 0);

    // std::string_view (7.9) wraps a C string safely: it stores a pointer AND
    // a length, and == compares the letters.
    std::println("string_view comparison:     {}", std::string_view{twin} == std::string_view{other_twin});

    // A C string function trusts you completely. Copying 20 characters into a
    // 16-byte array compiles fine and overwrites whatever lies after it:
    //     std::strcpy(editable, "a-very-long-sensor-name");
    // Never do this. std::string grows to fit.
    std::string name{label};
    name += "-north";
    std::println("\nstd::string: {} (size {})", name, name.size());

    // Old C functions want a const char*. A std::string will give you one, but
    // the pointer is only valid while the string is alive and unchanged.
    std::puts(name.c_str());

    std::println("\nargc = {}", argc);
    for (int i{0}; i < argc; ++i) {
        std::println("argv[{}] = {}", i, argv[i]);
    }

    return 0;
}
