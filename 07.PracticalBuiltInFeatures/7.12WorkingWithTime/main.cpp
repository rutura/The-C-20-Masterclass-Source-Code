#include <chrono>
#include <print>
#include <thread>
#include <vector>

// <chrono> is the standard library for time. Three ideas:
//   - a CLOCK tells you "what time is it now"
//   - a DURATION is a length of time (250ms, 3s, 2h)
//   - a TIME POINT is a specific instant, as measured by some clock

int main() {
    using namespace std::chrono_literals;   // enables 250ms, 3s, ...

    // --- durations ---

    // Literals give you readable durations. They have distinct types
    // (milliseconds, seconds, ...) and convert where it is lossless.
    std::chrono::milliseconds timeout{250ms};
    std::chrono::seconds      window{3s};
    auto total{window + timeout};            // common type: milliseconds
    std::println("timeout {}, window {}, total {}",
                 timeout, window, std::chrono::milliseconds{total});

    // count() drops the unit and hands back the raw number.
    std::println("timeout is {} ms", timeout.count());

    // --- measuring how long code takes ---

    // steady_clock never jumps backward (unlike a wall clock being
    // adjusted), so it is the right clock for measuring elapsed time.
    auto start{std::chrono::steady_clock::now()};

    std::vector<long long> data{};
    for (long long i{0}; i < 2'000'000; ++i) {
        data.push_back(i * i);
    }

    auto elapsed{std::chrono::steady_clock::now() - start};

    // duration_cast converts to the unit you want to report in.
    auto ms{std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)};
    std::println("built {} values in {}", data.size(), ms);

    // Sleep this thread for a duration - also expressed with a literal.
    std::this_thread::sleep_for(20ms);
    std::println("...woke up after 20ms");

    // --- calendar dates ---

    // system_clock is the wall clock - it maps to civil time.
    auto now{std::chrono::system_clock::now()};

    // floor to day precision, then view it as a year/month/day.
    auto today{std::chrono::floor<std::chrono::days>(now)};
    std::chrono::year_month_day date{today};
    std::println("today is {}", date);                      // 2025-09-10 style
    std::println("formatted: {:%Y-%m-%d}", date);
    std::println("year {}, month {}, day {}",
                 static_cast<int>(date.year()),
                 static_cast<unsigned>(date.month()),
                 static_cast<unsigned>(date.day()));

    // Build a specific date and do arithmetic on it.
    std::chrono::year_month_day deadline{std::chrono::year{2025},
                                         std::chrono::month{12},
                                         std::chrono::day{31}};
    std::println("deadline: {:%Y-%m-%d}", deadline);

    return 0;
}
