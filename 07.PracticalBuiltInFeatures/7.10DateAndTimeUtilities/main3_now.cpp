#include <print>
#include <chrono>
#include <locale>
#include <ctime>

// system_clock represents the UTC wall-clock time from the system-wide
// real-time clock - the clock to use for "what time is it right now."
int main() {
    // Setting the global locale makes formatted output follow the user's
    // own conventions (date order, month names, ...). See chapter 21 for a
    // full discussion of locales.
    std::locale::global(std::locale{""});

    // The L format specifier formats a time_point according to the
    // currently configured global locale.
    std::println("UTC: {:L}", std::chrono::system_clock::now());

    // %c is the locale's own "preferred" full date-and-time representation -
    // many more %-codes exist; consult a Standard Library reference for the
    // complete list.
    std::println("UTC: {:L%c}", std::chrono::system_clock::now());

    // is_steady reports whether a clock's time_point can ever go backward.
    // system_clock's is false - the OS clock can be adjusted at any time
    // (NTP sync, a user changing the time).
    std::println("system_clock::is_steady = {}", std::chrono::system_clock::is_steady);

    // system_clock additionally offers to_time_t()/from_time_t() to
    // interoperate with the C-style time_t representation from <ctime>.
    std::time_t as_time_t{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
    auto back_to_time_point{std::chrono::system_clock::from_time_t(as_time_t)};
    std::println("round-tripped through time_t: {:%Y-%m-%d %H:%M:%S}",
             std::chrono::time_point_cast<std::chrono::seconds>(back_to_time_point));
}
