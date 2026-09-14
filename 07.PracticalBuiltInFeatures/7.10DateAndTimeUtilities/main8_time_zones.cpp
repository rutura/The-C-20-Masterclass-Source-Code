#include <print>
#include <chrono>
#include <locale>

// NOTE FOR STUDENTS ON THE CLANG DOCKER IMAGE: as of Clang 21, libc++ does
// not yet implement the IANA time zone database (get_tzdb/locate_zone/
// zoned_time). This file compiles and runs correctly on MSVC and on GCC's
// libstdc++, which is what we build with. If you are on the Clang
// container, read along - you will not be able to build this one file.
int main() {
    using namespace std::chrono_literals;

    try {
        std::locale::global(std::locale{""});
    } catch (const std::runtime_error&) {
        std::println("(no OS locale available here - falling back to \"C\")");
    }

    // The time zone database ships with the library. get_tzdb() returns a
    // reference to it; .zones is every zone the database knows about.
    const auto& database{std::chrono::get_tzdb()};
    std::println("The tzdb knows about {} time zones.", database.zones.size());

    // locate_zone() looks a zone up by IANA name; current_zone() returns
    // whatever zone the machine itself is configured for.
    const auto* brussels{std::chrono::locate_zone("Europe/Brussels")};
    const auto* gmt{std::chrono::locate_zone("GMT")};
    const auto* current{std::chrono::current_zone()};
    std::println("This machine's current zone is: {}", current->name());
    (void)gmt;

    // Every time_point from system_clock is UTC. to_local() converts it to
    // the WALL-CLOCK time for a given zone.
    auto nowUTC{std::chrono::system_clock::now()};
    auto nowInBrussels{brussels->to_local(nowUTC)};
    auto nowInCurrentZone{current->to_local(nowUTC)};
    std::println("Now UTC:        {:L%c}", nowUTC);
    std::println("Now Brussels:   {:L%c}", nowInBrussels);
    std::println("Now in current: {:L%c}", nowInCurrentZone);

    // Construct a specific UTC time and convert it to Brussels' local time.
    auto t{std::chrono::sys_days{2020y / std::chrono::June / 22d} + 9h + 35min + 10s};   // UTC
    auto converted{brussels->to_local(t)};
    std::println("2020-06-22 09:35:10 UTC, in Brussels: {:L}", converted);

    // zoned_time pairs a time_point with a time_zone - formatting it prints
    // the correct wall-clock time for THAT zone directly, no manual
    // to_local() call needed.
    std::chrono::zoned_time<std::chrono::seconds> brusselsTime{
        brussels, std::chrono::local_days{2020y / std::chrono::June / 22d} + 9h};
    // Converting between zones is just constructing a new zoned_time from
    // an existing one - the underlying UTC instant stays the same.
    std::chrono::zoned_time<std::chrono::seconds> newYorkTime{
        "America/New_York", brusselsTime};
    std::println("Brussels: {:L}", brusselsTime.get_local_time());
    std::println("New York: {:L}", newYorkTime.get_local_time());
}
