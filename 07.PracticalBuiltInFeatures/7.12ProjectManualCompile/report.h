#pragma once

#include <string>
#include <string_view>

#include "stats.h"

namespace station {

std::string format_report(std::string_view sensor, const Summary& summary);

}   // namespace station
