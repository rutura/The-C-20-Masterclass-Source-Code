#include "utilities.h"

#include "containers_iterators_algorithms_01.h"
#include "containers_iterators_algorithms_02.h"

#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void containers_iterators_algorithms_01_demo()
{
  containers_iterators_algorithms_01::use_vector();
  containers_iterators_algorithms_01::use_list();
  containers_iterators_algorithms_01::use_deque();
}

void containers_iterators_algorithms_02_demo()
{
  containers_iterators_algorithms_02::use_set();
  /*
  containers_iterators_algorithms_02::use_map();
  containers_iterators_algorithms_02::use_multiset();
  containers_iterators_algorithms_02::use_multimap();
  */
}