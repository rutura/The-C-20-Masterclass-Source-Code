#pragma once

#include <fmt/format.h>


namespace Hello {
    unsigned int age{ 23 };

    namespace World {
        int local_var{ 44 };

        void say_something();
    }// namespace World

    void do_something();
}// namespace Hello