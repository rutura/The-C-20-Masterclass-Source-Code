#include "boxcontainer.h"

// Templated type alias
template<typename T> using compare_T = bool (*)(const T &, const T &);

template<typename T> T get_best(const BoxContainer<T> &collection, compare_T<T> comparator)
{
  T best = collection.get_item(0);
  for (size_t i{}; i < collection.size(); ++i) {

    if (comparator(collection.get_item(i), best)) { best = collection.get_item(i); }
  }
  return best;
}

bool larger_in_size(const std::string &str1, const std::string &str2)
{
  if (str1.size() > str2.size())
    return true;
  else
    return false;
}

bool greater_lexicographically(const std::string &str1, const std::string &str2) { return (str1 > str2); }

bool larger_int(const int &param1, const int &param2) { return param1 > param2; }


template<typename T> bool smaller(const T &param1, const T &param2)
{
  if (param1 < param2) { return true; }
  return false;
}

int main()
{

  BoxContainer<std::string> quote;
  quote.add("The");
  quote.add("sky");
  quote.add("is");
  quote.add("blue");
  quote.add("my");
  quote.add("friend");

  fmt::println("Gettting the best : ");
  fmt::println("larger in size : {}", get_best(quote, larger_in_size));
  fmt::println("greater lexicographicaly : {}", get_best(quote, greater_lexicographically));


  fmt::println("------------");

  BoxContainer<int> ints;
  ints.add(10);
  ints.add(3);
  ints.add(233);
  ints.add(23);
  ints.add(4);

  // fmt::println( "larger int : {}" , get_best(ints,larger_int) );
  fmt::println("smaller int : {}", get_best(ints, smaller));

  return 0;
}