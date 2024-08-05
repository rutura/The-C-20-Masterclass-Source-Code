module;

#include <fmt/format.h>

export module move_semantics_02;

namespace move_semantics_02{

    double add(double a, double b) { return a + b; }

    export void try_out_move_semantics(){

        int x{ 5 };
        int y{ 10 };

        int &&result = x + y;

        double &&outcome = add(10.1, 20.2);

        fmt::println("result : {}", result);
        fmt::println("outcome : {}", outcome);
    }
    
}   // namespace move_semantics_02