#include <array>
#include <cstddef>
#include <memory>
#include <print>
#include <span>
#include <string>
#include <utility>
#include <vector>

/*
    Chapter 9 assignment - Pointers and arrays

    Eight small jobs for the weather station: swapping, searching, reversing,
    spans, C strings, owning pointers, shared ownership, and hunting memory
    bugs.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
      - Exercises that ask you to "write" a function: declare a PROTOTYPE above
        main() and define the function below main(), like in chapter 6.
      - No `new` and no `delete` anywhere in your answers. Where a function
        must create memory, use the smart pointers from 9.10 and 9.11.
*/

// Provided for exercises 6 and 7. Its destructor only exists so you can SEE
// when a probe is destroyed (destructors are chapter 10).
struct Probe {
    std::string name;

    ~Probe() {
        std::println("  probe {} shut down", name);
    }
};

// Provided for exercise 7: a screen that shows one probe.
struct Dashboard {
    std::string title;
    std::shared_ptr<Probe> probe;
};

int main() {

    // A fixed dataset we will be working on. Fahrenheit.
    int readings[8]{68, 72, 59, 81, 90, 55, 77, 64};


    /*
        Exercise 1 - swapping, two ways

        Write two functions that swap the values of two ints:

            void swap_with_pointers(int* a, int* b);
            void swap_with_references(int& a, int& b);

        Call each one once on the same pair, `morning{68}` and `evening{75}`,
        and print the pair after each call. Because each call swaps again,
        the pair ends up back where it started.

        Sample output:
            after swap_with_pointers:   morning = 75, evening = 68
            after swap_with_references: morning = 68, evening = 75
    */
    std::println("--- Exercise 1: swapping ---");
    // TODO


    /*
        Exercise 2 - find the largest, with pointers only

        Write:

            const int* find_max(const int* first, const int* last);

        `first` and `last` describe a range of ints: from `first` up to, but not
        including, `last` (9.6). Return a pointer to the LARGEST element in the
        range, or nullptr if the range is empty. Walk the range with a pointer
        and ++, not with an index.

        Call it on the whole of `readings` (the end is `readings + 8`), then on
        an empty range (`readings` and `readings`). For a result that is not
        nullptr, print the value and its index. The index is the result minus
        `readings` (pointer subtraction).

        Sample output:
            largest = 90 at index 4
            empty range: no maximum
    */
    std::println("--- Exercise 2: find_max ---");
    // TODO


    /*
        Exercise 3 - reverse in place

        Write:

            void reverse_in_place(int* first, int* last);

        Reverse the elements from `first` up to but not including `last`, in
        the same memory. Use two pointers that start at the two ends and move
        toward each other, swapping what they point at (std::swap from
        <utility> is fine). Stop when they meet or cross. Remember that `last`
        is one PAST the final element, so the right-hand pointer must be
        stepped back before it is used.

        Make a working copy of the readings first, so `readings` stays intact:

            int working[8]{68, 72, 59, 81, 90, 55, 77, 64};

        Reverse all of `working` and print it. Then reverse only elements 1
        to 3 (`working + 1` up to `working + 4`) and print it again.

        Sample output:
            after reversing all:      64 77 55 90 81 59 72 68
            after reversing 1 to 3:   64 90 55 77 81 59 72 68
    */
    std::println("--- Exercise 3: reverse_in_place ---");
    // TODO


    /*
        Exercise 4 - one function for every kind of container

        Write:

            double average(std::span<const int> values);
            void clamp_all(std::span<int> values, int low, int high);

        `average` returns the mean of the values, or 0.0 for an empty span.
        `clamp_all` forces every element into the range low to high: anything
        below `low` becomes `low`, anything above `high` becomes `high`.

        Use these three containers (plus `readings` from the top):

            std::array<int, 4> evening{65, 70, 75, 80};
            std::vector<int> night{50, 95, 70, 62, 88};

        Print the average of `readings`, of `evening`, of `night`, and of only
        the first three elements of `readings` (a sub-span). Then call
        clamp_all(night, 60, 80) and print `night`.

        Sample output:
            readings:        70.75
            evening:         72.50
            night:           73.00
            first three:     66.33
            night clamped:   60 80 70 62 80
    */
    std::println("--- Exercise 4: spans ---");
    // TODO


    /*
        Exercise 5 - C strings

        Write:

            std::size_t count_char(const char* text, char target);
            void shout(char* text);

        `count_char` returns how many times `target` appears in the C string.
        Walk the string until the terminating '\0'; do not call std::strlen.

        `shout` changes every lowercase letter in the string to uppercase, IN
        PLACE. Use std::toupper from <cctype>, and cast each character to
        unsigned char before passing it (std::toupper's argument must be
        non-negative).

        Use:

            const char* log_line{"sensor-12 ok sensor-3 low sensor-27 ok"};
            char label[16]{"sensor-12"};

        Print how many '-' and how many ' ' are in log_line. Then shout() the
        label and print it. (log_line itself is read-only: why can you not
        shout() it?)

        Sample output:
            hyphens: 3, spaces: 5
            SENSOR-12
    */
    std::println("--- Exercise 5: C strings ---");
    // TODO


    /*
        Exercise 6 - owning pointers

        Write:

            std::unique_ptr<int[]> make_log(std::size_t capacity);
            std::unique_ptr<Probe> make_probe(const std::string& name);
            void retire(std::unique_ptr<Probe> probe);

        `make_log` returns an array of `capacity` ints holding 60, 61, 62, ...
        (use std::make_unique<int[]>, which starts every element at 0).
        `make_probe` returns a new Probe with that name.
        `retire` takes ownership of a probe: it prints "retiring <name>" and
        then simply returns, which destroys the probe.

        Make a log of 5 and print its elements. Make a probe called "north",
        pass it to retire() with std::move, and afterwards print whether the
        original unique_ptr is empty. Notice WHEN the "shut down" line appears.

        Sample output:
            log: 60 61 62 63 64
              retiring north
              probe north shut down
            probe in main is empty: true
    */
    std::println("--- Exercise 6: unique_ptr ---");
    // TODO


    /*
        Exercise 7 - shared ownership

        Using Probe and Dashboard from the top of the file (no new functions):

        1. Create a probe called "east" with std::make_shared. Print its
           use_count().
        2. In an inner { } scope, create three Dashboards that all show that
           probe, titled "wall", "phone" and "desk". Inside the scope, print
           use_count() again.
        3. After the scope, print use_count() once more.
        4. Create a std::weak_ptr to the probe and print whether it has
           expired. Then reset() the probe and print expired() again.

        Sample output:
            owners: 1
            owners with three dashboards: 4
            owners after the scope: 1
            watcher expired: false
              probe east shut down
            watcher expired: true
    */
    std::println("--- Exercise 7: shared_ptr and weak_ptr ---");
    // TODO


    /*
        Exercise 8 - hunt the bugs

        Here is a function that makes a backup copy of the readings. It
        compiles, and when you run it, it appears to work. It has TWO memory
        bugs:

            int* copy_readings(const int* data, std::size_t count) {
                int* copy{new int[count]};
                for (std::size_t i{0}; i <= count; ++i) {
                    copy[i] = data[i];
                }
                return copy;
            }

            // in main:
            int* backup{copy_readings(readings, 8)};
            std::println("backup[7] = {}", backup[7]);

        A. Put the code in a scratch copy of this file (not in your answers),
           build it with a sanitizer as in the project (9.12) and run it.
           A sanitizer reports the first problem it meets and stops. Read
           that report, fix the cause, build and run again, and read the
           second report. For each of the two, write down the line it points
           at and what the mistake is.

        B. Then write the fixed version in this file. It must not use `new`
           or `delete`, and it must not be possible to forget to free the
           copy:

               std::unique_ptr<int[]> copy_readings(const int* data, std::size_t count);

           Call it on `readings` with a count of 8 and print backup[7].

        Sample output (for B):
            backup[7] = 64
    */
    std::println("--- Exercise 8: hunt the bugs ---");
    // TODO

    return 0;
}
