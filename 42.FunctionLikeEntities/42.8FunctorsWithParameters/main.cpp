#include "boxcontainer.h"

// A functor can  take parameters and internally
//  store them as member variables
template<typename T> requires std::is_arithmetic_v<T> class IsInRange
{
public:
  IsInRange(T min, T max) : min_inclusive{ min }, max_inclusive{ max } {}
  bool operator()(T value) const { return ((value >= min_inclusive) && (value <= max_inclusive)); }

private:
  T min_inclusive;
  T max_inclusive;
};


template<typename T, typename RangePicker>
requires std::is_arithmetic_v<T> T range_sum(const BoxContainer<T> &collection, RangePicker is_in_range)
{

  T sum{};
  for (size_t i{}; i < collection.size(); ++i) {
    if (is_in_range(collection.get_item(i))) sum += collection.get_item(i);
  }
  return sum;
}

int main()
{

  BoxContainer<double> doubles;
  doubles.add(10.1);
  doubles.add(20.2);
  doubles.add(30.3);
  doubles.add(15);

  fmt::println("doubles : {}", doubles);
  fmt::println("range_sum :{} ", range_sum(doubles, IsInRange<double>(10.0, 15.5)));// 10.1
  fmt::println("range_sum :{} ", range_sum(doubles, IsInRange<double>(10.0, 41.5)));// 30.3


  fmt::println("------");
  /*
  BoxContainer<std::string> strings;
  strings.add("Hello");
  strings.add("World");

  range_sum(strings,IsInRange<std::string> ("Hello","World"));
  */

  fmt::println("-----");

  BoxContainer<int> ints;
  ints.add(10);
  ints.add(3);
  ints.add(6);
  ints.add(72);
  ints.add(23);
  ints.add(4);

  fmt::println("ints : {}", ints);
  fmt::println("range_sum :{} ", range_sum(ints, IsInRange<int>(10, 20)));// 10
  fmt::println("range_sum :{} ", range_sum(ints, IsInRange<int>(10, 30)));// 33


  return 0;
}