module;

#include <coroutine>
#include <fmt/core.h>
#include <cassert>

export module coro_basics_04;

namespace coro_basics_04{

    export template <typename T>
    struct generator {
        struct promise_type { 
            T m_value;
            generator get_return_object() { return generator(this); }    
            std::suspend_always initial_suspend() { return {}; }        
            std::suspend_always final_suspend() noexcept { return {}; }
        
            void unhandled_exception() noexcept {
                std::rethrow_exception(std::current_exception());
            }

            std::suspend_always yield_value(T val) {
                m_value = val; 
                return {};
            }

            void return_void() {
                fmt::println("Returning void...");
            }
        };

        generator(promise_type* p)
            : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
            
        ~generator() {
            fmt::println("Handle destroyed...");
            m_handle.destroy();
        }

        T operator()() {
            if(m_handle){
                m_handle.resume();
            }
            return m_handle.promise().m_value;
        }

        std::coroutine_handle<promise_type> m_handle;
    };

    export generator<int> generate_numbers() {
        fmt::println("generate_numbers starting");
        co_yield 10; // Return 10 and pause
        fmt::println("After stop point #1");

        co_yield 20;
        fmt::println("After stop point #2");

        co_yield 30;
        fmt::println("After stop point #3");
        fmt::println("generate_numbers ending");
    }

    export generator<int> infinite_number_stream(int start = 0) {
        auto value = start;
        for (int i = 0;; ++i) {
            co_yield value;
            ++value;
        }
    }

    export generator<int> range(int first, int last) {
        while (first != last) {
            co_yield first++;
        }
    }

}   //namespace coro_basics_04