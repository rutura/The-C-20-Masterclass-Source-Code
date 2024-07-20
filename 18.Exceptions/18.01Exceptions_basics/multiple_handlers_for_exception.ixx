module;

#include <fmt/format.h>

export module multiple_handlers_for_exception;

namespace multiple_handlers_for_exception{

    // Declarations
    export void f1();
    export void f2();
    export void f3();

    void exception_thrower()
    {
    fmt::println("starting exception_thrower()");
    throw 0;// Execution will half from here
    fmt::println("ending exception_thrower()");
    }

    // Definitions
    void f1()
    {
    fmt::println("Starting f1()");
    try {
        f2();
    } catch (int ex) {
        fmt::println("Exception handled in f1()");
    }
    fmt::println("Ending f1()");
    }

    void f2()
    {
    fmt::println("Starting f2()");
    try {
        f3();
    } catch (int ex) {
        fmt::println("Exception handled in f2()");
    }
    fmt::println("Ending f2()");
    }

    void f3()
    {
    fmt::println("Starting f3()");
    try {
        exception_thrower();
    } catch (int ex) {
        fmt::println("Exception handled in f3()");
    }
    fmt::println("Ending f3()");
    }

}   // namespace multiple_handlers_for_exception