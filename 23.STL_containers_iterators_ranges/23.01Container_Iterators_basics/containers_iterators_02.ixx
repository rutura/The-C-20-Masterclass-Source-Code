/*
    This code contains functions that print the contents of a collection, using iterators.
    The main goals is to introduce iterators.
    It can print both std::vector and std::array. Any container, as long as it has begin() and end() functions, can be printed.
    Most containers in the STL have these functions.
*/
module;

#include <fmt/format.h>

export module containers_iterators_02;

namespace containers_iterators_02{

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

    // We can adjust the beginning and end of the collection for printing.
    export template<typename T> 
    void print_collection(const T &collection, size_t begin_adjustment, size_t end_adjustment)
    {
        // Adjudt begining and end
        auto start_point = collection.begin() + begin_adjustment;
        auto end_point = collection.end() - end_adjustment;

        fmt::print(" [");
        while (start_point != end_point) {
            fmt::print(" {}", *start_point);
            ++start_point;
        }
        fmt::println(" ]");
    }

}   // namespace containers_iterators_02