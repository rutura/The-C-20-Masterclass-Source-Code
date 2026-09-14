#include <print>
#include <chrono>
#include <locale>

// system_clock represents the UTC wall-clock time from the system-wide
// real-time clock - the clock to use for "what time is it right now."
int main() {
    using namespace std;
    using namespace std::chrono;

    // Setting the global locale makes formatted output follow the user's
    // own conventions (date order, month names, ...). See chapter 21 for a
    // full discussion of locales.
    locale::global(locale{""});

    // The L format specifier formats a time_point according to the
    // currently configured global locale.
    println("UTC: {:L}", system_clock::now());

    // %c is the locale's own "preferred" full date-and-time representation -
    // many more %-codes exist; consult a Standard Library reference for the
    // complete list.
    println("UTC: {:L%c}", system_clock::now());
}
