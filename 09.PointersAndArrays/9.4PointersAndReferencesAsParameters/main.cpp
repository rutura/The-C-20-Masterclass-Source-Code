#include <print>
#include <vector>

// Both functions below swap the caller's two ints. They differ in what the
// caller writes and what the callee must check.
void swap_with_pointers(int* a, int* b) {
    int saved{*a};
    *a = *b;
    *b = saved;
}

void swap_with_references(int& a, int& b) {
    int saved{a};
    a = b;
    b = saved;
}

// A pointer can say "no answer", a reference cannot: a reference always refers
// to something. So a function that MIGHT find an element returns a pointer to
// it, or nullptr when there is none.
const int* find_first_above(const std::vector<int>& readings, int limit) {
    for (const int& reading : readings) {
        if (reading > limit) {
            return &reading;        // points INTO the caller's vector
        }
    }
    return nullptr;
}

// A pointer parameter can also be optional. Pass nullptr for any output you
// do not need, and the function skips it. A reference parameter cannot be
// left out.
void summarize(const std::vector<int>& readings, int* lowest, int* highest) {
    if (readings.empty()) {
        return;
    }

    int low{readings.front()};
    int high{readings.front()};

    for (int reading : readings) {
        if (reading < low) {
            low = reading;
        }
        if (reading > high) {
            high = reading;
        }
    }

    if (lowest != nullptr) {
        *lowest = low;
    }
    if (highest != nullptr) {
        *highest = high;
    }
}

// Never return the address of a local. The local is destroyed when the
// function returns, so the caller would receive a pointer to a dead object.
//
//     const int* broken() {
//         int local{72};
//         return &local;      // dangling the moment the function returns
//     }

int main() {

    int morning{68};
    int evening{75};

    // The caller must write & to hand over an address, which makes the
    // possible change visible at the call site.
    swap_with_pointers(&morning, &evening);
    std::println("after swap_with_pointers:   morning = {}, evening = {}", morning, evening);

    // A reference parameter is called like a normal function. The change is
    // invisible at the call site, which is why const references are the
    // default and non-const ones are used sparingly (6.8).
    swap_with_references(morning, evening);
    std::println("after swap_with_references: morning = {}, evening = {}", morning, evening);

    const std::vector<int> readings{68, 71, 69, 72, 70};

    const int* hot{find_first_above(readings, 70)};
    if (hot != nullptr) {
        std::println("\nfirst reading above 70 is {}, at index {}", *hot, hot - readings.data());
    }

    const int* scorching{find_first_above(readings, 100)};
    if (scorching == nullptr) {
        std::println("no reading above 100");
    }

    int lowest{0};
    int highest{0};
    summarize(readings, &lowest, &highest);
    std::println("\nlowest = {}, highest = {}", lowest, highest);

    // Only interested in the highest: pass nullptr for the one we skip.
    int just_highest{0};
    summarize(readings, nullptr, &just_highest);
    std::println("highest only = {}", just_highest);

    // Rule of thumb:
    //   must refer to something, always valid    -> reference
    //   may be absent, or may be repointed        -> pointer
    return 0;
}
