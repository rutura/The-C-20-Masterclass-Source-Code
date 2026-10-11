export module report;

import readings;                   // report depends on readings (and through it, on units)

export int hour_of_warmest(const Reading* readings, int count) {
    int best{0};
    for (int i{1}; i < count; ++i) {
        if (readings[i].celsius > readings[best].celsius) {
            best = i;
        }
    }
    return readings[best].hour;
}
