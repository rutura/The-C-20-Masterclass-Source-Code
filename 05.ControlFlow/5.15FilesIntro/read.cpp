#include <fstream>
#include <print>
#include <string>

// Part 2 of the file lecture: read the names back out and print them.
//
// std::ifstream ("input file stream") is the input side, the file
// counterpart of std::cin. std::getline reads one whole line at a time.

int main() {

    std::ifstream in{"names.txt"};

    // If the file isn't there, the stream fails to open. The usual cause
    // is running this before rooster_write, or running it from a
    // different working directory - see the lecture notes.
    if (!in) {
        std::println("Could not open names.txt. Run rooster_write first.");
        return 1;
    }

    // Same shape as `while (std::cin >> x)` from the switch lecture:
    // getline returns the stream, which tests false once there are no
    // more lines to read. So this loop runs once per line in the file.
    std::string name{};
    int count{0};
    while (std::getline(in, name)) {
        ++count;
        std::println("{}: {}", count, name);
    }

    std::println("Read {} names from names.txt", count);

    return 0;
}
