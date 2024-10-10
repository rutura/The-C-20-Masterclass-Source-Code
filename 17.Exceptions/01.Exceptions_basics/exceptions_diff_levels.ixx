module;

#include <fmt/format.h>

export module exceptions_diff_levels;

namespace exceptions_diff_levels{

    //Declarations
    export void f1();
    export void f2();
    export void f3();

    export void exception_thrower()
    {
        fmt::println("starting execution_thrower()");
        try {
            throw 0;// Execution will halt from here
        } catch (int ex) {
            fmt::println("Something went wrong");
        }
        fmt::println("ending execution_thrower()");
    }



    // Definitions

















}   // namespace exceptions_diff_levels