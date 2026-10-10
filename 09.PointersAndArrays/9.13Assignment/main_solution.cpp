#include <array>
#include <cctype>
#include <cstddef>
#include <memory>
#include <print>
#include <span>
#include <string>
#include <utility>
#include <vector>

/*
    Chapter 9 assignment - solutions
*/

struct Probe {
    std::string name;

    ~Probe() {
        std::println("  probe {} shut down", name);
    }
};

struct Dashboard {
    std::string title;
    std::shared_ptr<Probe> probe;
};

// ---------------------------------------------------------------------
// Exercise 1 - swapping, two ways
//
// The pointer version is called with &, and dereferences with *. The
// reference version is called like a normal function.
// ---------------------------------------------------------------------
void swap_with_pointers(int* a, int* b);
void swap_with_references(int& a, int& b);

// ---------------------------------------------------------------------
// Exercise 2 - find the largest, with pointers only
//
// nullptr is the "no answer" a reference could not give.
// ---------------------------------------------------------------------
const int* find_max(const int* first, const int* last);

// ---------------------------------------------------------------------
// Exercise 3 - reverse in place
//
// `last` is one PAST the final element, so it is stepped back before it is
// read. The pointers cross or meet in the middle.
// ---------------------------------------------------------------------
void reverse_in_place(int* first, int* last);

// ---------------------------------------------------------------------
// Exercise 4 - one function for every kind of container
// ---------------------------------------------------------------------
double average(std::span<const int> values);
void clamp_all(std::span<int> values, int low, int high);

// ---------------------------------------------------------------------
// Exercise 5 - C strings
// ---------------------------------------------------------------------
std::size_t count_char(const char* text, char target);
void shout(char* text);

// ---------------------------------------------------------------------
// Exercise 6 - owning pointers
// ---------------------------------------------------------------------
std::unique_ptr<int[]> make_log(std::size_t capacity);
std::unique_ptr<Probe> make_probe(const std::string& name);
void retire(std::unique_ptr<Probe> probe);

// ---------------------------------------------------------------------
// Exercise 8 - hunt the bugs
//
// The two bugs in the original:
//   1. "i <= count" reads data[count] and writes copy[count]: one element
//      past the end of both arrays (heap-buffer-overflow, at the loop).
//   2. The caller never deleted the returned array (a leak, reported
//      when the program exits).
// Returning a unique_ptr makes bug 2 impossible: the array is freed
// whenever the owner goes out of scope.
// ---------------------------------------------------------------------
std::unique_ptr<int[]> copy_readings(const int* data, std::size_t count);

int main() {

    int readings[8]{68, 72, 59, 81, 90, 55, 77, 64};

    std::println("--- Exercise 1: swapping ---");
    int morning{68};
    int evening{75};
    swap_with_pointers(&morning, &evening);
    std::println("after swap_with_pointers:   morning = {}, evening = {}", morning, evening);
    swap_with_references(morning, evening);
    std::println("after swap_with_references: morning = {}, evening = {}", morning, evening);

    std::println("\n--- Exercise 2: find_max ---");
    const int* largest{find_max(readings, readings + 8)};
    if (largest != nullptr) {
        std::println("largest = {} at index {}", *largest, largest - readings);
    }
    const int* none{find_max(readings, readings)};
    if (none == nullptr) {
        std::println("empty range: no maximum");
    }

    std::println("\n--- Exercise 3: reverse_in_place ---");
    int working[8]{68, 72, 59, 81, 90, 55, 77, 64};
    reverse_in_place(working, working + 8);
    std::print("after reversing all:      ");
    for (int value : working) {
        std::print("{} ", value);
    }
    std::println("");
    reverse_in_place(working + 1, working + 4);
    std::print("after reversing 1 to 3:   ");
    for (int value : working) {
        std::print("{} ", value);
    }
    std::println("");

    std::println("\n--- Exercise 4: spans ---");
    std::array<int, 4> evening_readings{65, 70, 75, 80};
    std::vector<int> night{50, 95, 70, 62, 88};
    std::println("readings:        {:.2f}", average(readings));
    std::println("evening:         {:.2f}", average(evening_readings));
    std::println("night:           {:.2f}", average(night));
    std::println("first three:     {:.2f}", average(std::span<const int>{readings}.first(3)));
    clamp_all(night, 60, 80);
    std::print("night clamped:   ");
    for (int value : night) {
        std::print("{} ", value);
    }
    std::println("");

    std::println("\n--- Exercise 5: C strings ---");
    const char* log_line{"sensor-12 ok sensor-3 low sensor-27 ok"};
    char label[16]{"sensor-12"};
    std::println("hyphens: {}, spaces: {}", count_char(log_line, '-'), count_char(log_line, ' '));
    shout(label);
    std::println("{}", label);
    // log_line points at a string literal, which is const data stored in
    // read-only memory: shout(log_line) would not compile (const char* to
    // char*), and a cast to force it would crash or be undefined behaviour.

    std::println("\n--- Exercise 6: unique_ptr ---");
    auto log{make_log(5)};
    std::print("log: ");
    for (std::size_t i{0}; i < 5; ++i) {
        std::print("{} ", log[i]);
    }
    std::println("");
    auto north{make_probe("north")};
    retire(std::move(north));
    std::println("probe in main is empty: {}", north == nullptr);

    std::println("\n--- Exercise 7: shared_ptr and weak_ptr ---");
    auto east{std::make_shared<Probe>("east")};
    std::println("owners: {}", east.use_count());
    {
        Dashboard wall{"wall", east};
        Dashboard phone{"phone", east};
        Dashboard desk{"desk", east};
        std::println("owners with three dashboards: {}", east.use_count());
    }
    std::println("owners after the scope: {}", east.use_count());
    std::weak_ptr<Probe> watcher{east};
    std::println("watcher expired: {}", watcher.expired());
    east.reset();
    std::println("watcher expired: {}", watcher.expired());

    std::println("\n--- Exercise 8: hunt the bugs ---");
    auto backup{copy_readings(readings, 8)};
    std::println("backup[7] = {}", backup[7]);

    return 0;
}

// --- Exercise 1 -------------------------------------------------------
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

// --- Exercise 2 -------------------------------------------------------
const int* find_max(const int* first, const int* last) {
    if (first == last) {
        return nullptr;
    }

    const int* largest{first};
    for (const int* p{first + 1}; p != last; ++p) {
        if (*p > *largest) {
            largest = p;
        }
    }
    return largest;
}

// --- Exercise 3 -------------------------------------------------------
void reverse_in_place(int* first, int* last) {
    while (first < last) {
        --last;                         // last is one past the end: step back first
        if (first == last) {
            break;                      // an odd count: both pointers reached the middle
        }
        std::swap(*first, *last);
        ++first;
    }
}

// --- Exercise 4 -------------------------------------------------------
double average(std::span<const int> values) {
    if (values.empty()) {
        return 0.0;
    }

    int total{0};
    for (int value : values) {
        total += value;
    }
    return static_cast<double>(total) / static_cast<double>(values.size());
}

void clamp_all(std::span<int> values, int low, int high) {
    for (int& value : values) {
        if (value < low) {
            value = low;
        }
        else if (value > high) {
            value = high;
        }
    }
}

// --- Exercise 5 -------------------------------------------------------
std::size_t count_char(const char* text, char target) {
    std::size_t count{0};
    for (const char* p{text}; *p != '\0'; ++p) {
        if (*p == target) {
            ++count;
        }
    }
    return count;
}

void shout(char* text) {
    for (char* p{text}; *p != '\0'; ++p) {
        *p = static_cast<char>(std::toupper(static_cast<unsigned char>(*p)));
    }
}

// --- Exercise 6 -------------------------------------------------------
std::unique_ptr<int[]> make_log(std::size_t capacity) {
    auto log{std::make_unique<int[]>(capacity)};
    for (std::size_t i{0}; i < capacity; ++i) {
        log[i] = 60 + static_cast<int>(i);
    }
    return log;
}

std::unique_ptr<Probe> make_probe(const std::string& name) {
    return std::make_unique<Probe>(name);
}

void retire(std::unique_ptr<Probe> probe) {
    std::println("  retiring {}", probe->name);
}   // probe goes out of scope here, and takes the Probe with it

// --- Exercise 8 -------------------------------------------------------
std::unique_ptr<int[]> copy_readings(const int* data, std::size_t count) {
    auto copy{std::make_unique<int[]>(count)};
    for (std::size_t i{0}; i < count; ++i) {         // < not <=
        copy[i] = data[i];
    }
    return copy;
}
