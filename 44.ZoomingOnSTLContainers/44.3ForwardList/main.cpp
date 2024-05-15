#include <fmt/format.h>
#include <forward_list>

template<typename T> void print_collection(const T &collection)
{

  auto it = collection.begin();

  fmt::print(" Collection [");
  while (it != collection.end()) {
    fmt::print(" {}", *it);
    ++it;
  }
  fmt::println("]");
}


int main()
{

  std::forward_list<int> numbers = { 100, 2, 3, 4, 5 };
  print_collection(numbers);

  // Code1 : Element access
  fmt::println(" front element : {}", numbers.front());


  // Modifiers

  fmt::println("---------------------");
  fmt::println("modifiers : ");

  // Clear
  fmt::println("clear :");
  print_collection(numbers);

  numbers.clear();

  print_collection(numbers);


  // Insert after
  fmt::println("insert_after : ");
  numbers = { 11, 12, 13, 14, 15 };

  print_collection(numbers);
  auto it_insert = numbers.before_begin();

  numbers.insert_after(it_insert, 333);

  print_collection(numbers);


  // Emplace after : create in place after an iterator
  fmt::println("emplace_after : ");

  print_collection(numbers);

  it_insert = numbers.before_begin();

  numbers.emplace_after(it_insert, 444);

  print_collection(numbers);


  // Erase_after
  fmt::println("erase_after : ");

  print_collection(numbers);

  auto it_erase = std::find(numbers.begin(), numbers.end(), 13);

  if (it_erase != numbers.end()) {
    fmt::println(" Found 13 !");
  } else {
    fmt::println(" Couldn't find 13 !");
  }

  // Erase the 14
  numbers.erase_after(it_erase);

  print_collection(numbers);


  // pop_front
  fmt::println("pop_front : ");

  print_collection(numbers);

  numbers.pop_front();

  print_collection(numbers);


  // resize : up or down
  fmt::println("resize : ");

  print_collection(numbers);

  numbers.resize(10);

  print_collection(numbers);

  numbers.resize(3);// When you resize down, the elements are lost for good.
                    // if you resize up again,you won't get them back.

  print_collection(numbers);

  numbers.resize(10);

  print_collection(numbers);


  // swap
  fmt::println("swap : ");

  std::forward_list<int> other_numbers{ 200, 400, 600 };

  fmt::print(" numbers : ");
  print_collection(numbers);

  fmt::print(" other_numbers :");
  print_collection(other_numbers);


  numbers.swap(other_numbers);

  fmt::print(" numbers : ");
  print_collection(numbers);

  fmt::print(" other_numbers :");
  print_collection(other_numbers);

  // Other operations
  fmt::println("merge : ");

  std::forward_list<int> numbers1{ 1, 5, 6 };
  std::forward_list<int> numbers2{ 9, 2, 4 };

  fmt::print(" numbers1 : ");
  print_collection(numbers1);

  fmt::print(" numbers2 : ");
  print_collection(numbers2);

  // merge
  numbers1.merge(numbers2);

  fmt::print(" numbers1 : ");
  print_collection(numbers1);

  fmt::print(" numbers2 : ");
  print_collection(numbers2);


  // splice_after : moving a range of elements from one container to another
  fmt::println("splice_after : ");

  numbers1 = { 1, 5, 6, 8, 3 };
  numbers2 = { 9, 2, 4, 7, 13, 11, 17 };

  fmt::print(" numbers1 : ");
  print_collection(numbers1);

  fmt::print(" numbers2 : ");
  print_collection(numbers2);

  numbers1.splice_after(numbers1.before_begin(), numbers2, numbers2.before_begin(), numbers2.cend());

  fmt::print(" numbers1 : ");
  print_collection(numbers1);

  fmt::print(" numbers2 : ");
  print_collection(numbers2);

  // Remove
  fmt::println("remove : ");

  numbers = { 1, 100, 2, 3, 10, 1, 11, -1, 12 };

  print_collection(numbers);

  numbers.remove(1);// remove both elements equal to 1

  print_collection(numbers);

  // Remove predicate
  numbers.remove_if([](int n) { return n > 10; });

  print_collection(numbers);


  // reverse
  fmt::println("reverse : ");

  numbers = { 1, 100, 2, 3, 10, 1, 11, -1, 12 };

  print_collection(numbers);

  numbers.reverse();

  print_collection(numbers);


  // Unique : Removes contiguous duplicates
  // Removes duplicated 100 and 11, but doesn't remove 1
  fmt::println("unique : ");

  numbers = { 1, 100, 100, 2, 3, 10, 1, 11, 11, -1, 12, 10, 1 };

  print_collection(numbers);

  numbers.unique();

  print_collection(numbers);


  // Sort
  fmt::println("sort : ");

  print_collection(numbers);

  numbers.sort();

  print_collection(numbers);

  // If we want to remove all duplicates, we can first sort and then
  // remove duplicates.

  numbers.unique();

  print_collection(numbers);

  return 0;
}