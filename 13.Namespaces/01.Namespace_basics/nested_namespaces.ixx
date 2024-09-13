module;

#include <fmt/format.h>

export module nested_namespaces;

namespace Hello {
    unsigned int age{ 23 };

    namespace World {
        int local_var{ 44 };

        export void say_something()
        {
            fmt::println("Hello there ");
            fmt::println("The age is : {}", age);
        }
    }// namespace World

    export void do_something()
    {
        // Here we don't have direct access to local_var, we have to go
        // through the namespace.
        fmt::println("Using local_var : {}", World::local_var);
    }
}// namespace Hello