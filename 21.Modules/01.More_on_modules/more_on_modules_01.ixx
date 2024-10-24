/*
    . Exploring block export: 
*/
module;

#include <fmt/format.h>
#include <iostream>
#include <string>
#include <cstring>

export module more_on_modules_01;

namespace more_on_modules_01{

    export{

        double add(double a, double b) {
            return a + b;
        }

        void greet(const std::string& name) {
            std::string dest;
            dest = "Hello ";
            dest.append(name);
            fmt::println("{}",dest);
        }
    }

    export void print_name_length(const char* c_str_name) {
        fmt::println("Length: {}",std::strlen(c_str_name));
    }

}   //namespace more_on_modules_01