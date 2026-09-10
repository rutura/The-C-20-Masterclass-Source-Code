#include <array>
#include <charconv>
#include <chrono>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <vector>

/*
    Chapter 7 assignment - Practical built-in features

    One small program built in seven steps. Each exercise pulls in a
    different facility from the chapter: std::array, std::vector, the
    sort / search / accumulate algorithms, std::string editing,
    <charconv> conversions, std::string_view parameters, enum class,
    type aliases, <chrono>, and std::optional.

    The theme is a tiny temperature-log tool: parse a handful of
    "YYYY-MM-DD,LABEL,VALUE" records, then summarise them.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
      - In sample runs, text after a ">" is what the user typed.
*/

// Raw records the whole program works on. Treat them as given.
inline constexpr std::array<std::string_view, 6> raw_records{
    "2025-03-01,roof,12.5",
    "2025-03-02,roof,14.0",
    "2025-03-03,roof,9.5",
    "2025-03-01,yard,11.0",
    "2025-03-02,yard,broken-sensor",   // exercise 5 must reject this one
    "2025-03-03,yard,13.5",
};

int main() {

    /*
        Exercise 1 - a fixed-size std::array of labels

        Declare  std::array<std::string_view, 2> stations{...}  holding
        "roof" and "yard". Print each with its index using a range-for
        with an init-statement:

            for (int i{0}; std::string_view s : stations) { ... ++i; }

        Sample output:
            station 0: roof
            station 1: yard
    */
    std::println("--- Exercise 1: station list ---");
    // TODO


    /*
        Exercise 2 - Temperature type alias + parse_value()

        Add near the top of the file:

            using Temperature = double;

        Write a function (prototype above main, definition below):

            std::optional<Temperature> parse_value(std::string_view text);

        It uses std::from_chars to parse `text` as a double. Return
        std::nullopt if the whole field is not a number (no exceptions).

        Test it on "13.5" and on "broken-sensor" and print the results.

        Sample output:
            parse_value("13.5")          -> 13.5
            parse_value("broken-sensor") -> (none)
    */
    std::println("--- Exercise 2: parse_value ---");
    // TODO


    /*
        Exercise 3 - split a record with std::string_view

        Write:

            struct Record {
                std::string date{};
                std::string station{};
                Temperature value{};
            };

            std::optional<Record> parse_record(std::string_view line);

        Split `line` on its two commas using find() and substr() on a
        string_view (no allocation until you build the Record). Reuse
        parse_value() for the third field. Return nullopt if there are
        not exactly three fields or the value does not parse.

        Parse every entry of raw_records into a std::vector<Record>,
        counting how many were rejected.

        Sample output:
            parsed 5 records, 1 rejected
    */
    std::println("--- Exercise 3: parse_record ---");
    // TODO


    /*
        Exercise 4 - min / max / average with the algorithms

        Given the std::vector<Record> from exercise 3, collect the
        values into a std::vector<Temperature>, then report:
          - the lowest  (std::ranges::min_element)
          - the highest (std::ranges::max_element)
          - the average (std::accumulate / sum divided by count)

        Sample output:
            low 9.5, high 14, average 12.1
    */
    std::println("--- Exercise 4: summary stats ---");
    // TODO


    /*
        Exercise 5 - Station enum + using enum

        Declare:

            enum class Station : std::uint8_t { Roof, Yard, Unknown };

        Write  Station station_from_text(std::string_view)  mapping
        "roof" -> Roof, "yard" -> Yard, anything else -> Unknown, and
        std::string_view station_name(Station) for the reverse (use
        `using enum Station;` inside its switch).

        Print each parsed record as:  <date>  <STATION>  <value>

        Sample output:
            2025-03-01  ROOF  12.5
            2025-03-02  ROOF  14
            ...
    */
    std::println("--- Exercise 5: station enum ---");
    // TODO


    /*
        Exercise 6 - sort records, newest value first

        Copy the records into a new vector and sort it with
        std::ranges::sort and a lambda comparing `value` descending.
        Print the sorted "<date> <station> <value>" lines.

        Sample output (highest value first):
            2025-03-02  roof  14
            2025-03-03  yard  13.5
            ...
    */
    std::println("--- Exercise 6: sort by value ---");
    // TODO


    /*
        Exercise 7 - which day is the record from? (<chrono>)

        Write:

            std::optional<std::chrono::year_month_day>
            parse_date(std::string_view yyyy_mm_dd);

        Parse the "YYYY-MM-DD" string with std::from_chars on the three
        slices. Return nullopt if the shape is wrong or the date is not
        .ok(). For each record, print the date formatted with
        std::println("{:%Y-%m-%d}", ymd) and its weekday via
        std::chrono::weekday{std::chrono::sys_days{ymd}}.

        Sample output:
            2025-03-01 is a Sat
            2025-03-02 is a Sun
            ...
    */
    std::println("--- Exercise 7: record dates ---");
    // TODO

    return 0;
}
