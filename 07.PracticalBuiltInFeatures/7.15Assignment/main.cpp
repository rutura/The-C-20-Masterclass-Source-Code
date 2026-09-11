#include <algorithm>
#include <chrono>
#include <format>
#include <numeric>
#include <print>
#include <ranges>
#include <regex>
#include <string>
#include <vector>

#include "rapidcsv.h"

/*
    Chapter 7 assignment - Practical built-in features

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
*/

int main() {

    // A fixed dataset we will be working on
    const std::vector<int> temperatures{68, 72, 59, 81, 90, 55, 77, 64};


    /*
        Exercise 1 - grow_readings(): building a vector with push_back

        Write:

            std::vector<int> grow_readings(const std::vector<int>& source,
                                            int extra);

        Start with an empty std::vector<int>, then push_back every
        element of `source` onto it one at a time (do not just copy-
        construct from source - the point is practicing push_back), and
        finally push_back the value `extra` once at the end.

        Call it with temperatures and 100, then print the resulting
        vector's size and its contents (a loop with a range-based for is
        fine).

        Sample output:
            size: 9
            68 72 59 81 90 55 77 64 100
    */
    std::println("--- Exercise 1: grow_readings ---");
    // TODO


    /*
        Exercise 2 - warmest_and_coolest(): sorting without disturbing the original

        Write:

            void warmest_and_coolest(const std::vector<int>& data,
                                      int& coolest, int& warmest);

        It must NOT sort `data` itself (it is const - the compiler will
        stop you if you try). Instead, make a local COPY of `data`, sort
        the copy with std::ranges::sort, and write the copy's first and
        last elements back through `coolest` and `warmest`.

        Call it on `temperatures`, then print both results, then print
        `temperatures` again to show it is unchanged (still in original
        order).

        Sample output:
            coolest = 55, warmest = 90
            temperatures (unchanged): 68 72 59 81 90 55 77 64
    */
    std::println("\n--- Exercise 2: warmest_and_coolest ---");
    // TODO


    /*
        Exercise 3 - average_of_hot_days(): a ranges/views pipeline

        Using std::views::filter and std::views::transform on
        `temperatures` (chained with |, no intermediate named vectors),
        build a view containing only the temperatures greater than 70,
        then use std::accumulate over that view (its .begin()/.end())
        to compute their average as a double. A "hot day" here just
        means "greater than 70" - no need for a separate function.

        Print how many hot-day readings there were and their average.

        Sample output:
            hot days: 4
            average: 80.00
    */
    std::println("\n--- Exercise 3: average_of_hot_days ---");
    // TODO


    /*
        Exercise 4 - clean_label(): string editing

        Write:

            std::string clean_label(std::string label);

        (label is taken BY VALUE on purpose - the function edits its own
        copy and returns it, leaving the caller's string untouched.)

        It should:
          1. erase everything from the first '#' onward, if the string
             contains one (use find + erase - if find returns npos,
             skip this step)
          2. replace every remaining space with an underscore (the same
             find-in-a-loop-and-replace pattern from the lecture)

        Call it on "sensor reading #3 (raw)" and print the result.

        Sample output:
            sensor_reading_
    */
    std::println("\n--- Exercise 4: clean_label ---");
    // TODO


    /*
        Exercise 5 - extract_reading(): parsing one line with istringstream

        Given one line of text shaped like:

            "sensor-7 42.5 ok"

        (a sensor name, a floating-point reading, and a status word),
        use a std::istringstream to extract the three fields into their
        own variables (std::string, double, std::string), then print
        them labeled on separate lines.

        Sample output:
            name: sensor-7
            reading: 42.5
            status: ok
    */
    std::println("\n--- Exercise 5: extract_reading ---");
    // TODO


    /*
        Exercise 6 - flagged_accounts(): CSV + regex together

        accounts.csv (already in this folder) has columns account, name,
        balance. Load it with rapidcsv::Document, same as 7.12ReadingCSV,
        and get the "name" and "balance" columns as vectors.

        A name is "flagged" if it matches this regex, checked with
        std::regex_match:

            std::regex short_name{"[A-Z][a-z]{0,3}"};

        (a capital letter followed by at most three lowercase letters -
        i.e. a name 4 characters or shorter). For every row where the
        name matches, print the name and its balance.

        Sample output (depends on accounts.csv's contents):
            Doe: 345.67
            Rich: 224.62
    */
    std::println("\n--- Exercise 6: flagged_accounts ---");
    // TODO


    /*
        Exercise 7 - format_receipt(): std::format spec grammar

        Write:

            std::string format_receipt(const std::string& item,
                                        int quantity, double price);

        Using std::format (not std::print - this function RETURNS a
        string), build one line shaped like a receipt row:

          - the item name, left-aligned, in a field 12 characters wide
          - the quantity, right-aligned, in a field 4 characters wide
          - the price, right-aligned, in a field 8 characters wide, with
            exactly 2 digits after the decimal point

        Call it three times, with ("coffee", 2, 4.5), ("bagel", 1, 3.25),
        and ("tea", 10, 2.0), and print each returned string.

        Sample output:
            coffee         2    4.50
            bagel          1    3.25
            tea           10    2.00
    */
    std::println("\n--- Exercise 7: format_receipt ---");
    // TODO


    /*
        Exercise 8 - days_until(): std::chrono calendar arithmetic

        Write:

            long days_until(std::chrono::year_month_day target);

        It should:
          1. get "today" as a year_month_day - system_clock::now(),
             floored to std::chrono::days, same as the lecture
          2. convert BOTH today and target to std::chrono::sys_days
             (year_month_day converts to sys_days implicitly through
             static_cast<std::chrono::sys_days>(...))
          3. subtract them (sys_days supports -, giving a std::chrono::days)
             and return .count() as a long

        Call it with a target date of your choosing that is after today
        (e.g. std::chrono::year{2026}/12/25 for a December 25 target -
        year_month_day can be built with the y/m/d operator/ syntax, not
        just the three-argument constructor from the lecture), and print
        the result.

        Sample output (the number will differ depending on today's date):
            42 days until 2026-12-25
    */
    std::println("\n--- Exercise 8: days_until ---");
    // TODO

    return 0;
}
