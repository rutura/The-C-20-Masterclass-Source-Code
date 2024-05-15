#include <cassert>
#include <coroutine>
#include <fmt/format.h>

template<typename T> struct generator
{
  struct promise_type
  {
    T m_value;
    generator get_return_object() { return generator(this); }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }

    void unhandled_exception() noexcept { std::rethrow_exception(std::current_exception()); }
    std::suspend_always yield_value(T val)
    {
      m_value = val;
      return {};
    }

    void return_void() { fmt::println("Returning void..."); }
  };
  generator(promise_type *p) : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
  ~generator()
  {
    fmt::println("Handle destroyed...");
    m_handle.destroy();
  }

  T operator()()
  {
    assert(m_handle != nullptr);
    m_handle.resume();
    return (m_handle.promise().m_value);
  }
  std::coroutine_handle<promise_type> m_handle;
};


generator<int> generate_numbers()
{
  fmt::println("generate_numbers starting");
  co_yield 10;// Return 10 and pause
  fmt::println("After stop point #1");

  co_yield 20;
  fmt::println("After stop point #2");

  co_yield 30;
  fmt::println("After stop point #3");
  fmt::println("generate_numbers ending");
}


generator<int> infinite_number_stream(int start = 0)
{
  auto value = start;
  for (int i = 0;; ++i) {
    // fmt::println( "In infinite_number stream..." );
    co_yield value;
    ++value;
  }
}


generator<int> range(int first, int last)
{
  while (first != last) { co_yield first++; }
}


int main()
{


  /*
  auto task1 = generate_numbers();

  fmt::println( "value : {}" , task1() );

  fmt::println("");
  fmt::println( "value : {}" , task1() );

  fmt::println("");
  fmt::println( "value : {}" , task1() );
  fmt::println( "coro done : {}" , task1.m_handle.done() );

  fmt::println("");
  task1();
  fmt::println( "coro done : {}" , task1.m_handle.done() );
  */

  /*
  auto task2 = infinite_number_stream();
  for(size_t i{}; ; ++i){
   fmt::println( "value : {}" , task2() );
  }
  */


  // Range
  auto task3 = range(0, 25);
  for (size_t i{}; i < 26; ++i) { fmt::println("value[{}] : {}", i, task3()); }


  fmt::println("Done!");

  return 0;
}