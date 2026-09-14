#include <print>
#include <chrono>
#include <locale>

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
}
