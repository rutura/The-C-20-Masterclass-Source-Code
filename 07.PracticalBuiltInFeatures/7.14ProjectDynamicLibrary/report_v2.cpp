#include "report.h"

#include <format>

namespace station {

// A second version of format_report(), for the "replace the library without
// relinking" step in the notes. Same name, same parameters, same return type,
// so main.cpp cannot tell the difference: only the text of the line changes.
// Build the library from stats.cpp and this file instead of report.cpp, copy
// it over the old one, and the same weather program prints the new line.
std::string format_report(std::string_view sensor, const Summary& summary) {
    return std::format("[v2] {}: min {:.1f} C, max {:.1f} C, mean {:.1f} C",
                       sensor,
                       to_celsius(summary.lowest),
                       to_celsius(summary.highest),
                       to_celsius(summary.average));
}

}   // namespace station
