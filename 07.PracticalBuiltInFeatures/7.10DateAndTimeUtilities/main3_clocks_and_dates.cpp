#include <print>
#include <chrono>
#include <locale>
#include <cmath>

// Two everyday questions about time need two different tools:
//   "what time is it right now?"   -> system_clock
//   "how long did that just take?" -> steady_clock
int main() {
    using namespace std::chrono_literals;

    // --- system_clock: "what time is it right now?" -----------------------
    // system_clock represents UTC wall-clock time from the system-wide
    // real-time clock - every time_point it returns is UTC, not your local
    // time. std::println understands a time_point directly, using the same
    // {:...} spec grammar from 7.8 - % codes replace a type letter like f
    // or d.
    auto now_utc{std::chrono::system_clock::now()};
    std::println("UTC:   {:%Y-%m-%d %H:%M:%S}", now_utc);

    // To show the time a student would actually recognize, convert that UTC
    // instant to their machine's own time zone. current_zone() asks the OS
    // which zone it's configured for; to_local() converts a UTC time_point
    // to that zone's wall-clock time.
    //
    // NOTE FOR STUDENTS ON THE CLANG DOCKER IMAGE: as of Clang 21, libc++
    // does not yet implement the IANA time zone database, so current_zone()
    // will fail to compile there. This works on MSVC and on GCC's
    // libstdc++, which is what we build with.
    auto now_local{std::chrono::current_zone()->to_local(now_utc)};
    std::println("Local: {:%Y-%m-%d %H:%M:%S}", now_local);

    // Setting the global locale makes formatted output follow the user's
    // own conventions (date order, month names, ...) - a SEPARATE axis from
    // the time zone conversion above. Locale changes how a time is WRITTEN;
    // it does not change WHICH instant or WHICH zone is being shown. The L
    // specifier formats according to the currently configured locale. See
    // chapter 21 for a full discussion of locales.
    try {
        std::locale::global(std::locale{""});
    } catch (const std::runtime_error&) {
        std::println("(no OS locale available here - falling back to \"C\")");
    }
    std::println("Local, locale-formatted: {:L%c}", now_local);

    // system_clock can be adjusted at any moment (NTP sync, a user changing
    // the time) - which is exactly why it's the WRONG tool for measuring
    // elapsed time. A different clock exists for that job.

    // --- steady_clock: "how long did that just take?" ---------------------
    // steady_clock is guaranteed to never go backward, unlike system_clock.
    // Take a reading before the work, another after, and subtract.
    auto start{std::chrono::steady_clock::now()};

    // Some work to time - arithmetic heavy enough that the loop doesn't
    // finish instantly.
    const int number_of_iterations{10'000'000};
    double d{0};
    for (int i{0}; i < number_of_iterations; ++i) {
        d += std::sqrt(std::abs(std::sin(i) * std::cos(i)));
    }

    auto end{std::chrono::steady_clock::now()};

    // end - start is a DURATION, not a time_point - subtracting two points
    // in time gives you the span between them. Every time_point is really
    // just a duration measured from its clock's own starting point (its
    // EPOCH) - system_clock's epoch is 1970-01-01; steady_clock's is
    // unspecified, since all that matters for timing is the DIFFERENCE
    // between two readings, never the absolute value.
    //
    //   timeline:   start ────────────── work happens ────────────── end
    //                 │                                                │
    //                 └──────────────────  diff = end - start ─────────┘
    //                                       (a DURATION, not a time_point)
    auto diff{end - start};

    // Use the result, otherwise an aggressive compiler might optimize the
    // entire loop away since d is never observed!
    std::println("d = {}", d);

    // Convert the difference into fractional milliseconds and print it.
    std::println("Total: {}", std::chrono::duration<double, std::milli>{diff});
    // duration_cast() gives whole milliseconds instead, if you don't need
    // the fractional part.
    std::println("Total: {}", std::chrono::duration_cast<std::chrono::milliseconds>(diff));

    // --- Dates: year_month_day ----------------------------------------------
    // C++20 added genuine calendar support to <chrono>. year, month, and day
    // are the building blocks; operator/ combines them into a full date, the
    // same natural order you'd say it out loud:
    auto some_date{2020y / std::chrono::June / 22d};   // year / month / day
    std::println("{:%Y-%m-%d}", some_date);

    // Named constants exist for all 12 months and the y/d literal suffixes
    // build year and day directly from a number - no need to spell out
    // std::chrono::year{2020} or std::chrono::day{22} by hand.

    // sys_days is the SERIAL counterpart to year_month_day - just a day
    // count since the epoch, and also a time_point (of system_clock, with
    // day precision). Converting between the two is how you go from "a
    // calendar date" to "a point in time you can compare/subtract" and back:
    std::chrono::sys_days as_time_point{some_date};             // date -> time_point
    std::chrono::year_month_day back_to_date{as_time_point};    // time_point -> date

    // floor<days> truncates any finer time_point down to midnight, which is
    // how you get "today" as a date from system_clock::now():
    auto today{std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
    std::chrono::year_month_day today_as_date{today};
    std::println("Today is {:%Y-%m-%d}", today_as_date);

    // Date arithmetic: sys_days supports +/- with a duration directly - the
    // most common case, adding/subtracting a number of days, just works.
    auto one_week_later{as_time_point + std::chrono::days{7}};
    std::println("One week after {:%Y-%m-%d} is {:%Y-%m-%d}",
                  some_date, std::chrono::year_month_day{one_week_later});

    // A full date WITH a time of day: add an hours/minutes/seconds duration
    // directly onto a sys_days.
    auto meeting_time{std::chrono::sys_days{2020y / std::chrono::June / 22d} + 9h + 35min};
    std::println("Meeting: {:%Y-%m-%d %H:%M}", meeting_time);
}
