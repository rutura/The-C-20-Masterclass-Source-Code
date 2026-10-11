#pragma once

// Provided for exercise 7: an old header, with its implementation in
// legacy_alarm.cpp. Do not change them. The exercise is to wrap them in a module.
#define ALARM_LEVELS 3                      // a macro: it will not cross the module boundary

struct Alarm {
    int level;
    const char* text;
};

Alarm make_alarm(int level, const char* text);
const char* describe_level(int level);
