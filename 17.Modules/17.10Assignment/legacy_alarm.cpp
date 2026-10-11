#include "legacy_alarm.h"

Alarm make_alarm(int level, const char* text) {
    return Alarm{level, text};
}

const char* describe_level(int level) {
    switch (level) {
        case 1:  return "notice";
        case 2:  return "warning";
        case 3:  return "critical";
        default: return "unknown";
    }
}
