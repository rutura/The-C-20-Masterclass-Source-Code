#include "report.h"

#include <format>

namespace station {

// Calls to_celsius(), which lives in stats.cpp. Both files go into the same
// library, so that call is resolved inside the library when it is linked.
// main.cpp never calls to_celsius itself. report_v2.cpp is a second version of
// this function that the notes swap in without relinking the program.
std::string format_report(std::string_view sensor, const Summary& summary) {
    return std::format("{}: low {:.1f} C, high {:.1f} C, average {:.1f} C",
                       sensor,
                       to_celsius(summary.lowest),
                       to_celsius(summary.highest),
                       to_celsius(summary.average));
}

}   // namespace station
