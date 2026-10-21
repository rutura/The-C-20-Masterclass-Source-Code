#pragma once

#include <string>
#include <string_view>

#include "station_api.h"
#include "stats.h"

namespace station {

STATION_API std::string format_report(std::string_view sensor, const Summary& summary);

}   // namespace station
