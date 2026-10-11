#include <algorithm>
#include <format>
#include <functional>
#include <iterator>
#include <numeric>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

/*
    Chapter 15 assignment - Algorithms, ranges and views

    Eight small jobs for the weather station. One rule for all of them: use
    the standard algorithms and views of this chapter, not a hand-written loop
    that does the same thing. (A loop to PRINT the result is fine.)

    Write any helper function ABOVE main(), and the lines that do the work in
    main() under the exercise's heading.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`
      - Prefer the std::ranges:: algorithms, with a projection where it helps.
*/

struct Reading {
    std::string station;
    int hour;
    double celsius;
};

// Provided. -99.0 is what a broken sensor reports.
const std::vector<Reading> table{
    {"north", 6, 11.5}, {"north", 12, 18.5}, {"north", 18, 15.0},
    {"south", 6, 14.0}, {"south", 12, 24.0}, {"south", 18, 20.5},
    {"east", 6, 12.5},  {"east", 12, 21.5},  {"east", 18, 17.0},
    {"west", 6, 9.0},   {"west", 12, 16.0},  {"west", 18, -99.0}};

// Provided.
bool is_broken(const Reading& r) {
    return r.celsius < -50.0;
}

// Provided: prints a label and the elements of a vector (a function template, as in 15.4).
template <typename T>
void show(std::string_view label, const std::vector<T>& values) {
    std::print("{:<16}", label);
    for (const T& value : values) {
        std::print(" {}", value);
    }
    std::println();
}

// Write your own helpers here, above main().


int main() {

    /*
        Exercise 1 - asking questions

        With the algorithms of 15.3, and the provided table and is_broken():
          - is any reading broken? (any_of)
          - how many readings are above 20 degrees? (count_if)
          - which reading is the first broken one? (find_if)
          - which valid reading is the coldest? Copy the valid readings into a
            new vector first (copy_if with std::back_inserter), then
            min_element with a PROJECTION: ranges::min_element(v, {}, &Reading::celsius).

        Sample output:
            any broken: true
            hot readings (above 20): 3
            first broken: west at 18h
            coldest valid: west at 6h (9)
    */
    std::println("--- Exercise 1: asking questions ---");
    // TODO


    /*
        Exercise 2 - copy and transform

        From the valid readings, keep the ones of station "south" (copy_if
        into a new vector) and convert their temperatures to Fahrenheit
        (transform into a vector<double>, f = c * 9 / 5 + 32). Print them
        with show().

        Sample output:
            south in F:      57.2 75.2 68.9
    */
    std::println("\n--- Exercise 2: copy and transform ---");
    // TODO


    /*
        Exercise 3 - erase_if and unique

        Copy the table into a vector and remove the broken readings with
        std::erase_if. Print how many were removed and how many are left.
        Then collect the hours of the remaining readings into a vector<int>
        (transform with the projection &Reading::hour), sort it, and remove the
        duplicates with unique followed by erase (15.4, 15.5). Print them.

        Sample output:
            removed 1, 11 left
            distinct hours:  6 12 18
    */
    std::println("\n--- Exercise 3: erase_if and unique ---");
    // TODO


    /*
        Exercise 4 - sort with projections

        Take the cleaned readings of exercise 3 and order them by station
        alphabetically, and inside each station by temperature, highest
        first. Do it with two stable_sort calls and projections (15.8): the
        minor key first, then the major key. Print the first six as
        "station hour temperature" with the format "{:<6} {:>2}h {:5.1f}".

        Sample output:
            east   12h  21.5
            east   18h  17.0
            east    6h  12.5
            north  12h  18.5
            north  18h  15.0
            north   6h  11.5
    */
    std::println("\n--- Exercise 4: sort with projections ---");
    // TODO


    /*
        Exercise 5 - binary search

        Put the temperatures of the cleaned readings into a sorted
        vector<double> (a pipeline of views ending in ranges::to, or
        transform plus back_inserter, then sort). With lower_bound, count
        how many are at least 15 and below 25: the difference of two iterators.

        Sample output:
            readings from 15 up to (not including) 25: 7
    */
    std::println("\n--- Exercise 5: binary search ---");
    // TODO


    /*
        Exercise 6 - numeric algorithms

        For the hourly rain {0, 2, 5, 0, 1, 7, 3, 0} (millimetres, the first
        value is for 6 o'clock): print the running total (inclusive_scan),
        the hour and amount of the wettest hour (max_element; hours start at
        6), and the average with std::reduce.

        Sample output:
            running total:   0 2 7 7 8 15 18 18
            wettest hour: 11h (7 mm)
            average: 2.25 mm
    */
    std::println("\n--- Exercise 6: numeric algorithms ---");
    // TODO


    /*
        Exercise 7 - a pipeline of views

        One pipeline, no loop: take the cleaned readings, keep those at hour 12,
        turn each into a std::string "station:temperature" (std::format("{}:{}", ...)),
        take the first three, join them with ", " (views::join_with) and
        collect the result into a std::string (ranges::to). Print it.

        Sample output:
            north:18.5, south:24, east:21.5
    */
    std::println("\n--- Exercise 7: a pipeline of views ---");
    // TODO


    /*
        Exercise 8 - average per station

        Get the distinct stations of the cleaned readings into a std::set
        (a view of &Reading::station finished with ranges::to<std::set>()). For
        each station, build a vector of its temperatures with a filter view and a
        transform view, and print the average with one decimal (use
        ranges::fold_left with std::plus<>{}). The set gives alphabetical order.

        Sample output:
            east: 17.0
            north: 15.0
            south: 19.5
            west: 12.5
    */
    std::println("\n--- Exercise 8: average per station ---");
    // TODO

    return 0;
}
