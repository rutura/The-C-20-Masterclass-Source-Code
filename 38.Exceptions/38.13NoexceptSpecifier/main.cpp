#include <fmt/format.h>

class Item
{
public:
  Item() {}

  void do_something_in_class() const noexcept
  {
    fmt::println("Doing something from class");
    try {
      throw 1;
    } catch (int ex) {
      fmt::println("Handling exception in Item::do_something_in_class");
      // throw; // Rethrowing in noexcept function/method will terminate program
    }
  }

private:
  int m_member_var;
};

void some_function() noexcept
{

  try {
    throw 1;
  } catch (int ex) {
    fmt::println("Handling int excpetion in free function some_function()");
    // throw;
  }
}

int main()
{

  // Exceptions can't be propagated out of a noexcept function by
  // any means, if you do so the program will terminate, you can
  // also see that the compiler gives you a warning about that.
  /*
      try{
              some_function();
      }catch(int ex){
              fmt::println( "Catching rethrown exception in main" );
      }
  */


  // Using noexcept member function
  Item item;
  try {
    item.do_something_in_class();
  } catch (int ex) {
    fmt::println("main() : Catching exception thrown from method");
  }

  return 0;
}