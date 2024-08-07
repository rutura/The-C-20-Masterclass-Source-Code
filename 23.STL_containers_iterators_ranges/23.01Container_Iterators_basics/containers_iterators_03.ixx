/*
    This code contains code that plays with constant iterators.
*/
module;

#include <fmt/format.h>

export module containers_iterators_03;

namespace containers_iterators_03{

    export template<typename T> 
    void print_collection(const T &collection)
    {

    auto it = collection.begin();

    fmt::print(" [");
    while (it != collection.end()) {
        fmt::print(" {}", *it);
        ++it;
    }
    fmt::println(" ]");
    }

}   // namespace containers_iterators_03