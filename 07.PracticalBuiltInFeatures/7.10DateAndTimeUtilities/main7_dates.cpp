#include <print>
#include <chrono>
#include <locale>
#include <iostream>

// C++20 added genuine calendar support to <chrono>. Only the Gregorian
// calendar ships with the standard, but the design allows other calendars
// (Coptic, Julian, ...) to interoperate with the rest of the library.
int main() {
    using namespace std;
    using namespace std::chrono;

    // locale{""} means "the user's own OS-configured locale" - it exists on
    // a normal Windows/Linux desktop, but a minimal container image (like
    // the Docker student environments for this course) may not have any
    // locale data installed beyond "C", so constructing it can throw there.
    // Guard it so the rest of the lecture still runs everywhere; on your own
    // machine this try block will simply succeed on the first attempt.
    try {
        locale::global(locale{""});
    } catch (const runtime_error&) {
        println("(no OS locale available here - falling back to \"C\")");
    }

    // --- The building-block calendrical types ------------------------------
    // year, month, day, and weekday are the atoms every date is built from.
    // Each has an ok() member that reports whether it holds a valid value.
    year y1{2020};
    auto y2{2020y};             // the y literal suffix does the same thing

    month m1{6};
    auto m2{June};              // named constants exist for all 12 months

    day d1{22};
    auto d2{22d};                // the d literal suffix

    // --- Building full dates with operator/ ---------------------------------
    // operator/ combines year/month/day in any of three natural orders.
    year_month_day fulldate1{2020y, June, 22d};
    auto fulldate2{2020y / June / 22d};    // Y/M/D
    auto fulldate3{22d / June / 2020y};    // D/M/Y

    // weekday_indexed: Monday[3] means "the 3rd Monday" of whatever month
    // it's combined with.
    year_month_day fulldate4{Monday[3] / June / 2020};

    // A month_day has no year yet - "June 22nd of some unspecified year."
    auto june22{June / 22d};
    // Attaching a year turns it into a full year_month_day.
    auto june22_2020{2020y / june22};

    // month_day_last: the last day of a month, year still unspecified.
    auto lastDayOfAJune{June / last};
    // year_month_day_last: the last day of June, for a specific year.
    auto lastDayOfJune2020{2020y / lastDayOfAJune};

    // year_month_weekday_last: the last Monday of June 2020.
    auto lastMondayOfJune2020{2020y / June / Monday[last]};

    // weekday_last (no month attached yet) and month_weekday /
    // month_weekday_last round out the full set of calendrical helper
    // types the standard provides:
    auto lastMondayOfAnyMonth{Monday[last]};              // weekday_last
    auto thirdMondayOfAnyJune{June / Monday[3]};          // month_weekday
    auto lastMondayOfAnyJune{June / Monday[last]};        // month_weekday_last
    auto juneOf2020{2020y / June};                        // year_month

    // --- sys_days: the serial-based counterpart to year_month_day ----------
    // sys_time<Duration> is a time_point of system_clock with a given
    // Duration. sys_days and sys_seconds are the two common precisions:
    //   using sys_days    = sys_time<days>;
    //   using sys_seconds = sys_time<seconds>;
    // sys_days is SERIAL - just a day count since the epoch. year_month_day
    // is FIELD-BASED - separate year/month/day members. Arithmetic-heavy
    // code is faster on the serial form; human-readable output wants the
    // field-based form.

    // Today, as a sys_days: floor<days> truncates now() to midnight.
    auto today{floor<days>(system_clock::now())};

    // Convert a year_month_day to a time_point via sys_days.
    system_clock::time_point t1{sys_days{2020y / June / 22d}};

    // And the opposite conversion: time_point -> year_month_day.
    year_month_day yearmonthday{floor<days>(t1)};
    year_month_day today2{floor<days>(system_clock::now())};

    // A full date WITH a time of day: 2020-06-22 09:35:10 UTC.
    auto t2{sys_days{2020y / June / 22d} + 9h + 35min + 10s};

    // --- Printing dates ------------------------------------------------------
    // operator<< works on ostreams just like any other type.
    cout << yearmonthday << '\n';
    // println()/format() understand chrono types directly; the L specifier
    // formats according to the current global locale.
    println("{:L}", yearmonthday);

    // Careful: printing a year_month_weekday_last prints its SYMBOLIC form,
    // not a resolved calendar date.
    println("{:L}", lastMondayOfJune2020);       // "2020/Jun/Mon[last]"
    // Converting through sys_days resolves it to an actual date first.
    year_month_day lastMondayOfJune2020YMD{sys_days{lastMondayOfJune2020}};
    println("{:L}", lastMondayOfJune2020YMD);    // "2020-06-29"

    // With the L specifier, month/weekday names are localized. %A prints
    // the full weekday name instead of an abbreviation. Naming a specific
    // locale like "nl-NL" only works if that locale's data is installed on
    // the machine - guarded here for the same reason as locale{""} above.
    try {
        locale::global(locale{"nl-NL"});
        println("Monday in Dutch is {:L%A}", Monday);
    } catch (const runtime_error&) {
        println("(nl-NL locale not installed here - skipping)");
    }
    locale::global(locale::classic());   // restore to the default "C" locale

    // --- Arithmetic with dates ------------------------------------------------
    auto t3{t2 + days{5}};       // add 5 days to t2
    auto t4{t3 + years{1}};      // add 1 year to t3
    println("t2 + 5 days + 1 year -> {:L}", t4);

    // A trap: sys_days (and any time_point) is a SERIAL type. Adding
    // years{1} to it does not mean "same date, next year" - the standard
    // defines a chrono year as the AVERAGE Gregorian year (365.2425 days),
    // to stay leap-year-correct over many additions. That average is not a
    // whole number of days, so the time-of-day component can visibly drift.
    auto t5{sys_days{2020y / June / 22d} + 9h + 35min + 10s};
    auto t6{t5 + years{1}};
    println("t5 = {:L}", t5);   // 2020-06-22 09:35:10
    println("t6 = {:L}", t6);   // 2021-06-22 15:24:22  <- time drifted!

    // To add EXACTLY one calendar year, split into a field-based
    // year_month_day plus the remaining time-of-day, add the year on the
    // field-based type (where "a year" means exactly that), then rebuild
    // the serial time_point from the pieces.
    sys_days t5_days{time_point_cast<days>(t5)};
    seconds t5_seconds{t5 - t5_days};
    year_month_day t5_ymd{t5_days};
    year_month_day t7_ymd{t5_ymd + years{1}};
    auto t7{sys_days{t7_ymd} + t5_seconds};
    println("t7 = {:L}", t7);   // 2021-06-22 09:35:10  <- time preserved
}
