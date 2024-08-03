module;

#include <fmt/format.h>

export module functors_04;

namespace functors_04{

    export void lambda_sandbox(){

        int result = [](int x, int y) -> int { return x + y; }(7, 3);
        fmt::println("{}", result);


        // Auto type deduction can help deduce the type of the generated lambda function
        // We don't have access to that in our C++ code.
        auto func = [](int x, int y) -> int { return x + y; };
        result = func(10, 20);
        fmt::println("{}", result);

    }
}   // namespace functors_04