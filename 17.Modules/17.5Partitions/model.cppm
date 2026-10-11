// An interface partition: `forecast:model` is a part of the module `forecast`.
module;

#include <vector>

export module forecast:model;

export struct Reading {
    int hour;
    double celsius;
};

export struct Series {
    std::vector<Reading> readings;
};
