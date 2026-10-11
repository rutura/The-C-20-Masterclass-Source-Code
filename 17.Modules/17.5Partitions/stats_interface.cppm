module;

#include <vector>

export module forecast:stats;

import :model;                     // use another partition (not exported again from here)

export double mean_of(const Series& series);
export double spread_of(const Series& series);       // standard deviation
