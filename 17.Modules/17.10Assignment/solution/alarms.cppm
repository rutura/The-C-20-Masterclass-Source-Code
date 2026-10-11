module;

#include "legacy_alarm.h"

export module alarms;

export using ::Alarm;
export using ::make_alarm;
export using ::describe_level;

export constexpr int alarm_levels{ALARM_LEVELS};
