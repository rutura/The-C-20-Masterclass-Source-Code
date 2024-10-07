/*
    . Highliting that the final and override specifiers are not reserved keywords.
        . You can use them as variable names, class names, function names etc.
        . This very bad though!
        . Don't!
*/
module;

#include <fmt/format.h>

export module inh_poly_2;

namespace inh_poly_2{

    class final{
        //DONT' DO THIS
    };

    export void override(){ // DON'T DO THIS EITHER.
        fmt::println("The override function being called...");
    }
    
} // namespace inh_poly_2