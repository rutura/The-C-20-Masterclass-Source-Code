#include <cstdint>
#include <print>

// This lecture is concepts, not new C++ syntax - nothing here needs a
// new keyword. The point is to turn "memory is a street of numbered
// mailboxes" into something you can point at on your own machine: real
// addresses, for real variables.
//
// The "&" below just asks "where does this variable live?" - pointers
// themselves are chapter 09's topic. reinterpret_cast<std::uintptr_t>
// turns that address into a plain number std::println can print.
// NOTES.md walks through what that number actually means, and why a
// 64-bit machine's addresses are not themselves 64 bits of USABLE
// range.

int main() {
    int width{4};
    int height{3};

    auto width_address{reinterpret_cast<std::uintptr_t>(&width)};
    auto height_address{reinterpret_cast<std::uintptr_t>(&height)};

    std::println("width  lives at address 0x{:x}", width_address);
    std::println("height lives at address 0x{:x}", height_address);

    auto gap{height_address > width_address
                 ? height_address - width_address
                 : width_address - height_address};
    std::println("the two addresses are {} bytes apart", gap);

    std::println("an address on this machine is {} bytes wide", sizeof(void*));

    return 0;
}

// Try it: run this a few times in a row. The two addresses move around
// between runs (the OS deliberately randomizes where the stack starts
// each time - a security feature called ASLR) but stay the SAME
// distance apart within any one run, because that distance is decided
// by the compiler, not the OS.
