// The GLOBAL MODULE FRAGMENT: everything between `module;` and the module
// declaration is ordinary textual inclusion, exactly as in a header. This is
// where a module that needs the standard library puts its #includes.
module;

#include <string>
#include <vector>

export module stations;

export struct Station {
    std::string name;
    std::vector<double> readings;
};

// DECLARATIONS only. The bodies are in stations.cpp, the implementation unit,
// so a change to a body does not touch this file or the files that import it.
export double mean_of(const Station& station);
export double largest_of(const Station& station);

// A template must be defined in the interface: whoever instantiates it needs
// the body, as in 6.13.
export template <typename T>
T clamped(T value, T low, T high) {
    return value < low ? low : (value > high ? high : value);
}

// `export { ... }` exports everything inside the braces.
export {
    Station make_station(std::string name, std::vector<double> readings);
    bool is_empty(const Station& station);
}
