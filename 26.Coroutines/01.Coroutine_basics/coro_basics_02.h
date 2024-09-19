#pragma once

#include <coroutine>
#include <fmt/core.h>


namespace coro_basics_02 {

struct CoroType
{
  struct promise_type
  {
    int m_value;
    CoroType get_return_object() { return CoroType(this); }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }

    void unhandled_exception() noexcept { std::rethrow_exception(std::current_exception()); }

    std::suspend_always yield_value(int val)
    {
      m_value = val;
      return {};
    }

    void return_void() {};
  };

  CoroType(promise_type *p)
    : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}

  ~CoroType()
  {
    fmt::println("Handle destroyed...");
    m_handle.destroy();
  }

  std::coroutine_handle<promise_type> m_handle;
};

inline CoroType do_work()
{
  fmt::println("Starting the coroutine...");
  co_yield 1;
  co_yield 2;
  co_yield 3;
  co_return;
}

}//namespace coro_basics_02