module;

#include <coroutine>
#include <fmt/core.h>

export module coro_basics_01;

namespace coro_basics_01{

    export struct CoroType {
        struct promise_type { 
            CoroType get_return_object() { return CoroType(this); }    
            std::suspend_always initial_suspend() { return {}; }        
            std::suspend_always final_suspend() noexcept{ return {}; }
        
            void unhandled_exception() noexcept
            {
                std::rethrow_exception(std::current_exception());
            }
            void return_void(){};
        
        };
        CoroType(promise_type* p)
            : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
        ~CoroType()
        {
            fmt::println("Handle destroyed...");
            m_handle.destroy();
        }
        std::coroutine_handle<promise_type>   m_handle;
    };

    export CoroType do_work() {
        fmt::println("Doing first thing...");
        co_await std::suspend_always{};
        fmt::println("Doing second thing...");
        co_await std::suspend_always{};
        fmt::println("Doing third thing...");
    }

}   //namespace coro_basics_01