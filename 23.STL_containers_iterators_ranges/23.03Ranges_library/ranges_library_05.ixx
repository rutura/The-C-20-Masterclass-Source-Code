module;

#include <fmt/format.h>

export module ranges_library_05;

namespace ranges_library_05{

    export void print(auto view)
    {
    for (auto i : view) {// Computation happens here.
        fmt::print("{} ", i);
    }
    fmt::println("");
    }
        
}   // namespace ranges_library_05