module;

#include <fmt/format.h>

export module final_override_not_keywords;

namespace final_override_not_keywords{

    class final{
        //DONT' DO THIS

    };

    export void override(){
        fmt::println("The override function being called...");
    }

}   // namespace final_override_not_keywords