#include <cstring>
#include <fmt/format.h>

// Regular class template
template<typename T> class Adder
{
public:
  Adder() {}
  T add(T x, T y);
  void do_something() { fmt::println("Doing something..."); }
};

template<typename T> T Adder<T>::add(T a, T b) { return a + b; }


// Template specialization
template<> class Adder<char *>
{
public:
  Adder() {}
  char *add(char *a, char *b);
};

// template <> //  <= this is not needed if defined outside of class
inline char *Adder<char *>::add(char *a, char *b) { return strcat(a, b); }
