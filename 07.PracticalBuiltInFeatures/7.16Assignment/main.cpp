#include <algorithm>
#include <chrono>
#include <format>
#include <numeric>
#include <print>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

/*
    Chapter 7 assignment - Practical built-in features

    Five small jobs for one imaginary weather station: sorting, functional
    style, string formatting, dates and durations, and regex.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
      - Exercises that ask you to "write" a function: put the function
        below main() and declare it above main(), like in chapter 6.
*/

int main() {

    // Fixed datasets we will be working on. Temperatures are in Fahrenheit.
    const std::vector<int> temperatures{68, 72, 59, 81, 90, 55, 77, 64};
    const std::vector<std::string> sensor_ids{
        "sensor-12", "sensor-3", "sensor-27", "sensor-8", "sensor-1"};
    const std::vector<std::string> raw_lines{
        "sensor-7 42.5 ok #calibrated", "sensor-12 8.25 low", "sensor-3 100 ok #spare"};
    const std::string log_line{
        "14:06:09 ERROR sensor-7 temp=91, "
        "14:07:12 WARN sensor-12 temp=88, "
        "14:09:45 INFO sensor-3 temp=71"};


    /*
        Exercise 1 - Sorting and searching: the sensor registry

        Part A. `sensor_ids` is the list of registered sensors, in no
        particular order. A monitoring screen needs to answer "is this
        sensor registered?" over and over, so sort once and then binary
        search. Make a COPY of sensor_ids, sort it alphabetically with
        std::ranges::sort, and print it.

        Then write:

            bool is_registered(const std::vector<std::string>& sorted_ids,
                                const std::string& id);

        It must use std::ranges::binary_search. Call it on your sorted
        copy with "sensor-27" and with "sensor-99", and print both answers.

        Part B. The screen also wants the ids listed longest first. Make a
        second copy of sensor_ids and sort it with a LAMBDA comparator:
        longer ids come first, and ids of the same length come in
        alphabetical order. (Without that tie-break, the order of equal-
        length ids is not something std::ranges::sort promises.) Print it.

        Remember the precondition: binary_search only gives a trustworthy
        answer on data sorted the way it expects (ascending). That is why
        Part B works on its own copy and never touches the one Part A
        searches.

        Part C. Write:

            std::vector<int> top_n(const std::vector<int>& data, std::size_t n);

        It returns the `n` largest values of `data`, largest first. It
        must NOT sort `data` itself (it is const, the compiler will stop
        you). Make a local copy, sort the copy with std::ranges::greater{},
        then build the result by push_back-ing the first `n` elements onto
        an empty vector. Take care not to read past the end if `data` has
        fewer than `n` elements.

        Call it on `temperatures` with n = 3 and print the result.

        Sample output:
            sorted: sensor-1 sensor-12 sensor-27 sensor-3 sensor-8
            sensor-27 registered: true
            sensor-99 registered: false
            by length: sensor-12 sensor-27 sensor-1 sensor-3 sensor-8
            top 3: 90 81 77
    */
    std::println("--- Exercise 1: sorting and searching ---");
    // TODO


    /*
        Exercise 2 - Functional style: views and accumulate

        `temperatures` are in Fahrenheit.

        Part A. Using std::views::filter and std::views::transform
        (chained with |, no intermediate named vectors), build ONE view
        that:

          1. keeps only the "hot days", i.e. temperatures greater than 70
          2. converts each of those to Celsius: (f - 32) * 5.0 / 9.0

        Then use std::accumulate over that view (its .begin()/.end()) to
        get the number of hot days and their average Celsius temperature.

        Hints:
          - The view is lazy: nothing is filtered or converted until
            something iterates it.
          - Celsius values are fractional, so the starting value of the
            sum must be a double (0.0), not an int (0). Otherwise every
            partial sum is truncated back to an int.
          - Counting is a fold too. Give accumulate a starting value of 0
            and a lambda that ignores the element and returns the count
            plus one.

        Part B. Find the hottest reading in `temperatures` with
        std::accumulate and a lambda: start from the first element, and
        let the lambda keep whichever of "best so far" and "current
        element" is larger. No loop, no variable updated by hand.

        Sample output:
            hot days: 4
            average: 26.67
            hottest: 90
    */
    std::println("\n--- Exercise 2: functional style ---");
    // TODO


    /*
        Exercise 3 - Strings and formatting: a station table

        `raw_lines` holds lines shaped like:

            "sensor-7 42.5 ok #calibrated"

        (a sensor name, a reading, a status, and sometimes a "#..."
        comment at the end). Turn them into a neat table.

        Write two functions:

            std::string_view sensor_number(std::string_view name);

        If `name` starts with "sensor-", return the rest of it (just the
        number part); otherwise return `name` unchanged. Use starts_with
        and remove_prefix: it should not create or copy any std::string,
        it only moves the window of the view. Careful: the view you get
        back points into the caller's text, so only use it while that
        text is still alive.

            std::string format_row(std::string_view number, double reading,
                                    const std::string& status);

        Using std::format (not std::print, this function RETURNS a
        string), build one table row from three columns separated by
        " | ":

          - the sensor number, right-aligned, 3 characters wide
          - the status, centered, 6 characters wide
          - the reading, right-aligned, 8 characters wide, with exactly
            2 digits after the decimal point

        Then, for every line in `raw_lines`:
          1. copy it and, if the copy contains a '#', erase everything
             from the '#' onward (find + erase; if find returns npos,
             skip this step)
          2. parse the copy with a std::istringstream into a name, a
             reading (double) and a status
          3. print format_row(sensor_number(name), reading, status)

        Print the header line first. It uses the same widths and
        alignments; the header words are "id", "status" and "reading".

        Sample output:
             id | status |  reading
              7 |   ok   |    42.50
             12 |  low   |     8.25
              3 |   ok   |   100.00
    */
    std::println("\n--- Exercise 3: strings and formatting ---");
    // TODO


    /*
        Exercise 4 - Dates and durations

        Part A. Write:

            long long days_until(std::chrono::year_month_day target);

        It should:
          1. get "today": std::chrono::system_clock::now(), floored to
             std::chrono::days, same as the lecture. The result is
             already a std::chrono::sys_days.
          2. convert `target` to std::chrono::sys_days too, so both
             dates are in the same "day number since the epoch" shape
          3. subtract them (sys_days - sys_days gives a std::chrono::days)
             and return .count()

        Call it with a target date of your choosing that is after today.
        year_month_day can be built with the year/month/day operator/
        syntax, e.g. std::chrono::year{2030} / 1 / 1 for January 1st,
        2030. Print the result, with the date formatted as {:%Y-%m-%d}.

        Part B. A technician worked three shifts: 4 hours, 90 minutes and
        45 seconds. Add the three durations together directly (different
        units mix freely, chrono picks the common one) and print the
        total with {}. Then:

          - split the total into hours, minutes and seconds with
            std::chrono::hh_mm_ss, and print them as "5h 30m 45s"
          - use std::chrono::duration_cast to print how many WHOLE
            minutes the total is

        Sample output (the first number will differ depending on today's
        date):
            1180 days until 2030-01-01
            total on duty: 19845s
            5h 30m 45s
            330 whole minutes
    */
    std::println("\n--- Exercise 4: dates and durations ---");
    // TODO


    /*
        Exercise 5 - Regex

        Part A. Write:

            bool is_valid_sensor_id(const std::string& id);

        A valid id is the text "sensor-" followed by one to three digits,
        and NOTHING else. Use std::regex_match, and a raw string literal
        for the pattern (\d is a regex metacharacter, so R"(...)" saves
        you from doubling the backslash).

        Test it on "sensor-7", "sensor-1234", "Sensor-7" and "sensor-7 "
        (note the trailing space) and print each with its verdict.

        Part B. `log_line` holds several readings shaped like
        "sensor-7 temp=91". Walk EVERY one of them with a
        std::sregex_iterator (remember: the regex must be a NAMED
        variable, not a temporary) and a pattern with two capture groups,
        one for the sensor id and one for the number. Convert the number
        with std::stoi, print each reading as "<sensor>: <temperature>",
        and keep track of the hottest one with a plain if.

        Part C. Export the same readings as CSV with std::regex_replace:
        one "number,temperature" line per reading, dropping everything
        else. This takes a pattern with two capture groups, a replacement
        using $1 and $2, and the std::regex_constants::format_no_copy
        flag. Catch what regex_replace returns (the original is never
        modified) and print it.

        Sample output:
            [sensor-7] -> true
            [sensor-1234] -> false
            [Sensor-7] -> false
            [sensor-7 ] -> false
            sensor-7: 91
            sensor-12: 88
            sensor-3: 71
            hottest: 91
            7,91
            12,88
            3,71
    */
    std::println("\n--- Exercise 5: regex ---");
    // TODO

    return 0;
}
