#include <cstddef>
#include <cstdint>
#include <memory>
#include <print>
#include <string_view>
#include <vector>

#if defined(_MSC_VER) && defined(_DEBUG)
    #include <crtdbg.h>
    // Make every "new" in this file remember its file and line, so the
    // leak report can point at the line that allocated.
    #define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// PROJECT: Memory Detective.
//
// A weather station program with SEVEN memory bugs planted in it, one per
// case. Every bug compiles without a warning, and most of them even appear to
// work. Pick a case on the command line and run it with a sanitizer to see how
// the tools catch what the compiler cannot:
//
//     detective heap-overflow           the buggy version
//     detective heap-overflow fixed     the corrected version
//
// Read the buggy function, find the mistake yourself FIRST, then run it.

// ---------------------------------------------------------------------------
// 1. heap-overflow: a log of the last 8 readings, filled one slot too far.
// ---------------------------------------------------------------------------
void heap_overflow_buggy() {
    const std::size_t capacity{8};
    int* log{new int[capacity]{}};

    for (std::size_t i{0}; i <= capacity; ++i) {          // BUG: <= goes one past the end
        log[i] = 60 + static_cast<int>(i);
    }

    std::println("last slot holds {}", log[capacity - 1]);
    delete[] log;
}

void heap_overflow_fixed() {
    const std::size_t capacity{8};
    int* log{new int[capacity]{}};

    for (std::size_t i{0}; i < capacity; ++i) {
        log[i] = 60 + static_cast<int>(i);
    }

    std::println("last slot holds {}", log[capacity - 1]);
    delete[] log;
}

// ---------------------------------------------------------------------------
// 2. stack-overflow: summing a local array, one element too many.
// ---------------------------------------------------------------------------
void stack_overflow_buggy() {
    int readings[5]{68, 71, 69, 72, 70};
    int total{0};

    for (std::size_t i{0}; i <= 5; ++i) {                 // BUG: readings[5] does not exist
        total += readings[i];
    }

    std::println("total = {}", total);
}

void stack_overflow_fixed() {
    int readings[5]{68, 71, 69, 72, 70};
    int total{0};

    for (int reading : readings) {                        // cannot go past the end
        total += reading;
    }

    std::println("total = {}", total);
}

// ---------------------------------------------------------------------------
// 3. use-after-free: reading a reading that was already given back.
// ---------------------------------------------------------------------------
void use_after_free_buggy() {
    int* latest{new int{72}};
    std::println("latest = {}", *latest);

    delete latest;

    int stale{*latest};                                   // BUG: the memory is gone
    std::println("latest after delete = {}", stale);
}

void use_after_free_fixed() {
    int* latest{new int{72}};
    std::println("latest = {}", *latest);

    delete latest;
    latest = nullptr;                                     // a stale pointer is now detectable

    if (latest != nullptr) {
        std::println("latest after delete = {}", *latest);
    }
    else {
        std::println("no latest reading any more");
    }
}

// ---------------------------------------------------------------------------
// 4. double-free: two pointers to one reading, both deleted.
// ---------------------------------------------------------------------------
void double_free_buggy() {
    int* primary{new int{68}};
    int* backup{primary};                                 // a second name, NOT a second reading

    delete primary;
    delete backup;                                        // BUG: the same memory, freed twice

    std::println("both deleted");
}

void double_free_fixed() {
    auto primary{std::make_unique<int>(68)};              // exactly one owner, one delete
    const int* backup{primary.get()};                     // a borrowed view, never deleted

    std::println("primary = {}, backup sees {}", *primary, *backup);
}

// ---------------------------------------------------------------------------
// 5. leak: every sample is allocated and none is ever freed.
// ---------------------------------------------------------------------------
void leak_buggy() {
    for (int i{0}; i < 3; ++i) {
        int* sample{new int{60 + i}};                     // BUG: no delete, the address is lost
        std::println("sample {} = {}", i, *sample);
    }
}

void leak_fixed() {
    for (int i{0}; i < 3; ++i) {
        auto sample{std::make_unique<int>(60 + i)};       // freed at the end of each pass
        std::println("sample {} = {}", i, *sample);
    }
}

// ---------------------------------------------------------------------------
// 6. stale-pointer: a pointer into a vector that then grows.
// ---------------------------------------------------------------------------
void stale_pointer_buggy() {
    std::vector<int> readings{68, 71, 69};
    const int* first{&readings[0]};

    readings.push_back(72);                               // full: moves every element elsewhere

    int stale{*first};                                    // BUG: the old storage was freed
    std::println("first = {}", stale);
}

void stale_pointer_fixed() {
    std::vector<int> readings{68, 71, 69};

    readings.push_back(72);

    const int* first{&readings[0]};                       // take the address AFTER growing
    std::println("first = {}", *first);
}

// ---------------------------------------------------------------------------
// 7. signed-overflow: adding up readings in an int that is too small.
//    Only the undefined-behaviour sanitizer (GCC, Clang) notices this one.
// ---------------------------------------------------------------------------
void signed_overflow_buggy() {
    int total{2'000'000'000};
    int more{500'000'000};

    total += more;                                        // BUG: does not fit in an int

    std::println("total = {}", total);
}

void signed_overflow_fixed() {
    std::int64_t total{2'000'000'000};
    std::int64_t more{500'000'000};

    total += more;

    std::println("total = {}", total);
}

// ---------------------------------------------------------------------------

void print_usage() {
    std::println("usage: detective <case> [fixed]");
    std::println("");
    std::println("  heap-overflow     writes past the end of a new[] array");
    std::println("  stack-overflow    reads past the end of a local array");
    std::println("  use-after-free    reads through a pointer after delete");
    std::println("  double-free       deletes the same memory twice");
    std::println("  leak              allocates and never frees");
    std::println("  stale-pointer     keeps a pointer into a vector that grew");
    std::println("  signed-overflow   int arithmetic that does not fit");
}

int main(int argc, char* argv[]) {

#if defined(_MSC_VER) && defined(_DEBUG)
    // Debug builds on MSVC can report leaks when the program ends. Send the
    // report to the console instead of only to the debugger's Output window.
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    if (argc < 2) {
        print_usage();
        return 0;
    }

    const std::string_view name{argv[1]};
    const bool fixed{argc >= 3 && std::string_view{argv[2]} == "fixed"};

    if (name == "heap-overflow") {
        fixed ? heap_overflow_fixed() : heap_overflow_buggy();
    }
    else if (name == "stack-overflow") {
        fixed ? stack_overflow_fixed() : stack_overflow_buggy();
    }
    else if (name == "use-after-free") {
        fixed ? use_after_free_fixed() : use_after_free_buggy();
    }
    else if (name == "double-free") {
        fixed ? double_free_fixed() : double_free_buggy();
    }
    else if (name == "leak") {
        fixed ? leak_fixed() : leak_buggy();
    }
    else if (name == "stale-pointer") {
        fixed ? stale_pointer_fixed() : stale_pointer_buggy();
    }
    else if (name == "signed-overflow") {
        fixed ? signed_overflow_fixed() : signed_overflow_buggy();
    }
    else {
        std::println("unknown case: {}\n", name);
        print_usage();
        return 1;
    }

    return 0;
}
