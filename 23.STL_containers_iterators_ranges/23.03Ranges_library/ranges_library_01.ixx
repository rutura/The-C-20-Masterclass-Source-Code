module;

#include <fmt/format.h>

export module ranges_library_01;

namespace ranges_library_01{

    export template<typename T> 
    void print_collection(const T &collection)
    {

    fmt::print(" Collection [");
    for (const auto &elt : collection) { fmt::print(" {}", elt); }
    fmt::print("]");
    }

}   // namespace ranges_library_01 