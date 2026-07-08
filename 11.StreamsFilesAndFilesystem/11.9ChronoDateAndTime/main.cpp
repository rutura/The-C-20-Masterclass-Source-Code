// A CSV row or a ledger line often needs a date alongside its data - "which
// semester", "when was this expense logged". <chrono> (C++20) is the
// standard library's calendar/clock library: another kind of data a real
// program persists, right alongside the file contents this chapter has
// spent its other seven lectures on.

#include <print>
#include <chrono>

int main() {

    // std::chrono::system_clock::now() reads the current wall-clock time -
    // a time_point, not a calendar date yet.
    auto now = std::chrono::system_clock::now();
    std::println("Raw time_point : {}", now);

    // year_month_day is the calendar type - a date with no time-of-day
    // component. floor<days> truncates the time_point down to whole days
    // before year_month_day can be constructed from it.
    std::chrono::year_month_day today{std::chrono::floor<std::chrono::days>(now)};
    std::println("Today's date   : {}", today);

    // year_month_day can also be built directly from its three parts.
    // std::chrono::day/std::chrono::year are ordinary constructors here -
    // the y/d literal suffixes exist too, but need
    // `using namespace std::chrono_literals` in scope, which this lecture
    // deliberately avoids per this course's no-using-namespace convention.
    std::chrono::year_month_day semesterStart{
        std::chrono::year{2025}, std::chrono::September, std::chrono::day{2}};
    std::println("Semester start : {}", semesterStart);

    // Individual fields are accessible on their own, each as its own
    // strong type (std::chrono::year, std::chrono::month, std::chrono::day) -
    // not plain ints, so you can't accidentally swap month and day.
    std::println("");
    std::println("year  : {}", int{semesterStart.year()});
    std::println("month : {}", unsigned{semesterStart.month()});
    std::println("day   : {}", unsigned{semesterStart.day()});

    // std::format's chrono specifiers control exactly how a date prints -
    // the same {} mini-language from chapter 5, now covering dates too.
    std::println("");
    std::println("Default          : {}", semesterStart);
    std::println("ISO-like {{:%Y-%m-%d}} : {:%Y-%m-%d}", semesterStart);
    std::println("Long form {{:%B %d, %Y}} : {:%B %d, %Y}", semesterStart);

    return 0;
}
