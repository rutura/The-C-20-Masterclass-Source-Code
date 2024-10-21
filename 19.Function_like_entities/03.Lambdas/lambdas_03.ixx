/*
    .#3: Capturing by reference under the hood
*/
module;

#include <fmt/format.h>

export module lambdas_03;

namespace lambdas_03{

    export void capturing_by_ref_under_the_hood(){
        int a{ 7 };
        int b{ 3 };
        int some_var{ 28 };// Not captured by the [=] lambda, so it won't set up a member var  for this
        double some_other_var{ 55.5 };// Not captured by the [=] lambda, so it won't set up   a member var for this.


        // Capturing a few variables by reference
        auto func = [&a, &b](int c, int d) {
            ++a;// Modifying member vars allowed by default.
            fmt::println("Captured values : ");
            fmt::println(" a : {}", a);
            fmt::println(" b : {}", b);

            fmt::println("Parameters : ");
            fmt::println(" c : {}", c);
            fmt::println(" d : {}", d);
        };

        func(10, 20);
        fmt::println("a : {}", a);
    }

}   // namespace lambdas_03