module;

#include <cppcoro/generator.hpp>

export module practical_coro_01;

namespace practical_coro_01 {

    export cppcoro::generator<const std::uint64_t> fibonacci()
    {
    std::uint64_t a = 0, b = 1;
    while (true)
    {
        co_yield b;
        auto tmp = a;
        a = b;
        b += tmp;
    }
    }

}   //namespace practical_coro_01