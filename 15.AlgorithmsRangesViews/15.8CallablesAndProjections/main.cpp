#include <algorithm>
#include <functional>
#include <map>
#include <print>
#include <string>
#include <string_view>
#include <vector>

struct Reading {
    std::string station;
    int hour;
    double celsius;
};

void show(std::string_view label, const std::vector<Reading>& readings) {
    std::print("{:<28}", label);
    for (const auto& r : readings) {
        std::print(" {}{}:{}", r.station.substr(0, 1), r.hour, r.celsius);
    }
    std::println();
}

// 1. A plain function.
bool is_hot_function(double celsius) {
    return celsius > 20.0;
}

// 2. A function object: a class with operator() (12.6) that can carry state.
struct HotterThan {
    double limit;
    bool operator()(double celsius) const { return celsius > limit; }
};

int main() {

    std::vector<double> temperatures{18.5, 24.0, 21.5, 12.5, 16.0, 20.5};

    // Every algorithm that takes "a function" takes anything CALLABLE.
    // Six different things, one question: how many are above 20?
    std::println("--- six kinds of callable");
    auto lambda{[](double c) { return c > 20.0; }};
    std::function<bool(double)> stored{lambda};                      // can hold any of them
    auto bound{std::bind_back(std::greater<>{}, 20.0)};              // fixes the SECOND argument: x > 20.0

    std::println("function pointer: {}", std::ranges::count_if(temperatures, is_hot_function));
    std::println("function object:  {}", std::ranges::count_if(temperatures, HotterThan{20.0}));
    std::println("lambda:           {}", std::ranges::count_if(temperatures, lambda));
    std::println("std::function:    {}", std::ranges::count_if(temperatures, stored));
    std::println("bind_back:        {}", std::ranges::count_if(temperatures, bound));
    double limit{20.0};
    std::println("lambda with a capture: {}", std::ranges::count_if(temperatures, [limit](double c) { return c > limit; }));

    // A seventh kind of callable you have not met: a POINTER TO A MEMBER.
    // &Reading::celsius is not the temperature of any reading. It means "the
    // celsius member of a Reading", to be applied to a particular Reading later.
    // std::invoke(callable, arguments...) calls any callable in the same way,
    // and for a member pointer, "calling" it means reading that member of the
    // object you pass.
    Reading sample{"south", 12, 24.0};
    auto which_member{&Reading::celsius};
    std::println("\nstd::invoke(which_member, sample) = {}", std::invoke(which_member, sample));
    // Because of that, an algorithm that wants "a function that takes a Reading"
    // accepts &Reading::celsius: it is the shortest way to say "look at the celsius".

    // A PROJECTION: "look at this part of each element". Every std::ranges
    // algorithm takes one, after the comparison.
    std::vector<Reading> readings{
        {"north", 6, 11.5}, {"north", 12, 18.5}, {"north", 18, 15.0},
        {"south", 6, 14.0}, {"south", 12, 24.0}, {"south", 18, 20.5},
        {"east", 6, 12.5},  {"east", 12, 21.5},  {"east", 18, 17.0}};

    std::println("\n--- projections");
    show("start:", readings);

    // sort(range, comparison, projection). {} means "the default comparison".
    std::vector<Reading> by_temperature{readings};
    std::ranges::sort(by_temperature, {}, &Reading::celsius);
    show("sorted by temperature:", by_temperature);

    // The projection is applied to both sides of every comparison, so the
    // comparison itself stays the ordinary one. Descending: change only that.
    std::ranges::sort(by_temperature, std::ranges::greater{}, &Reading::celsius);
    show("hottest first:", by_temperature);

    // Sorting by two keys: stable_sort by the minor key first, then by the major
    // key. Equal majors keep their minor order because the sort is stable.
    std::vector<Reading> grouped{readings};
    std::ranges::stable_sort(grouped, {}, &Reading::hour);
    std::ranges::stable_sort(grouped, {}, &Reading::station);
    show("by station, then hour:", grouped);

    // Finding and extremes use projections too.
    auto warmest{std::ranges::max_element(readings, {}, &Reading::celsius)};
    std::println("\nwarmest: {} at {}h ({})", warmest->station, warmest->hour, warmest->celsius);
    auto first_south{std::ranges::find(readings, "south", &Reading::station)};    // compare the PROJECTED value with "south"
    std::println("first south reading: {}h", first_south->hour);

    // A projection can be a lambda, too. (stable_sort: "east" and "west" have the
    // same length, and plain sort does not say which of them comes first.)
    std::vector<std::string> names{"east", "north", "west", "south"};
    std::ranges::stable_sort(names, {}, [](const std::string& name) { return name.size(); });
    std::print("\nnames by length:");
    for (const auto& name : names) {
        std::print(" {}", name);
    }
    std::println();

    // The algorithm may COPY your callable, so state kept inside it is lost.
    std::println("\n--- stateful callables are copied");
    struct Counter {
        int calls{0};
        bool operator()(double c) { ++calls; return c > 20.0; }
    };
    Counter counter;
    auto hot{std::ranges::count_if(temperatures, counter)};
    std::println("found {} hot, but the counter object says {} calls (the algorithm worked on a copy)", hot, counter.calls);

    // Three ways to see the state: a reference capture, std::ref, or the
    // value that for_each hands back.
    int calls{0};
    hot = std::ranges::count_if(temperatures, [&calls](double c) { ++calls; return c > 20.0; });
    std::println("reference capture:  {} calls (found {})", calls, hot);

    Counter by_reference;
    hot = std::ranges::count_if(temperatures, std::ref(by_reference));
    std::println("std::ref(counter):  {} calls (found {})", by_reference.calls, hot);

    auto [end, finished]{std::ranges::for_each(temperatures, Counter{})};
    std::println("for_each returns the callable: {} calls", finished.calls);

    // std::function: one type for any callable with the same signature, so
    // they can live in a container. The price is an indirect call, and
    // sometimes an allocation; prefer a lambda or a template parameter when
    // you do not need to store it.
    std::println("\n--- std::function in a table");
    std::map<std::string, std::function<double(double)>> conversions{
        {"to fahrenheit", [](double c) { return c * 9.0 / 5.0 + 32.0; }},
        {"to kelvin", [](double c) { return c + 273.0; }},
        {"doubled", [](double c) { return c * 2.0; }}};
    for (const auto& [name, convert] : conversions) {
        std::println("{:<14} {}", name, convert(20.0));
    }
    return 0;
}
