#include <chrono>
#include <exception>
#include <fmt/format.h>
#include <thread>

void our_terminate_function()
{
  fmt::println("Our custom terminate function called");
  fmt::println("Program will terminate in 10s ...");
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));// Wait 10 more seconds
  std::abort();
}


int main()
{

  // std::set_terminate(&our_terminate_function);
  std::set_terminate([]() {
    fmt::println("Our custom terminate function called");
    fmt::println("Program will terminate in 10s ...");
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));// Wait 10 more seconds
    std::abort();
  });

  throw 1;

  return 0;
}