#include "report.h"

#include <format>

namespace station {

// Calls to_celsius(), which lives in stats.cpp. Compiling this file alone
// leaves that call as an undefined symbol in report's object file (UNDEF in
// dumpbin, U in nm): the linker fills it in later, or reports an error if no
// object file defines it.
std::string format_report(std::string_view sensor, const Summary& summary) {
    return std::format("{}: low {:.1f} C, high {:.1f} C, average {:.1f} C",
                       sensor,
                       to_celsius(summary.lowest),
                       to_celsius(summary.highest),
                       to_celsius(summary.average));
}

}   // namespace station
