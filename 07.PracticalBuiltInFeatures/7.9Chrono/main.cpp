#include <print>
#include <chrono>
#include <format>
#include <thread>
#include <vector>

int main() {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    // --- durations: an amount of time, with a UNIT baked into the type ----
    // std::chrono::duration<Rep, Period> counts Rep ticks of length Period.
    // The standard ships named aliases so you rarely spell that out:
    // std::chrono::seconds, milliseconds, minutes, hours, ...
    seconds fiveSeconds{5};
    milliseconds fiveThousandMs{5000};

    // Different duration TYPES, same amount of time - duration_cast
    // converts between them explicitly (narrowing conversions, like
    // double -> int, are not implicit here either).
    std::println("fiveSeconds == fiveThousandMs: {}",
                  fiveSeconds == fiveThousandMs);

    // The _s / _ms / _min literal suffixes (chrono_literals) are a
    // shorter way to write the same thing.
    auto raceDuration{90min + 32s};   // 90 minutes and 32 seconds
    std::println("raceDuration in seconds: {}",
                  duration_cast<seconds>(raceDuration).count());

    // --- benchmarking a block of code with steady_clock --------------------
    // steady_clock never goes backward (not tied to the wall clock, so it
    // is unaffected by the system clock being adjusted) - the right clock
    // for MEASURING elapsed time.
    const auto start{steady_clock::now()};

    std::vector<int> squares;
    for (int i{0}; i < 1'000'000; ++i) {
        squares.push_back(i * i);
    }

    const auto end{steady_clock::now()};
    const auto elapsed{duration_cast<milliseconds>(end - start)};

    std::println("Squaring 1,000,000 numbers took {} ms", elapsed.count());

    // --- wall-clock time with system_clock ----------------------------------
    // system_clock tracks real calendar time - the one to use for "what
    // time is it right now", timestamps, and logging. Unlike steady_clock,
    // it CAN jump (NTP sync, a user changing the clock).
    const auto now{system_clock::now()};

    // std::format understands time_point directly, using the same {:...}
    // spec grammar from 7.7, with % chrono format codes instead of a type
    // letter like 'f' or 'd'. Rounding to seconds first keeps the printed
    // time readable - an unrounded time_point prints with its full
    // sub-second precision, right down to nanoseconds.
    const auto nowToTheSecond{time_point_cast<seconds>(now)};
    std::println("Right now: {:%Y-%m-%d %H:%M:%S}", nowToTheSecond);

    // --- C++20 calendar types: year_month_day -------------------------------
    // A time_point is a point on a timeline; year_month_day is a genuine
    // CALENDAR DATE - built from chrono's year/month/day building blocks.
    const year_month_day releaseDate{year{2020}, month{9}, day{15}};
    std::println("C++20 was published around: {:%B %d, %Y}", releaseDate);

    // floor<days> truncates a time_point down to midnight, so it can
    // convert to a year_month_day - a time_point on its own carries no
    // notion of "calendar day" until you floor it to that granularity.
    const year_month_day today{floor<days>(now)};
    std::println("Today's date: {}", today);

    // Calendar arithmetic in days - useful for "N days from now" style
    // calculations without hand-rolling month-length rules.
    const year_month_day nextWeek{floor<days>(now) + days{7}};
    std::println("One week from today: {}", nextWeek);

    return 0;
}
