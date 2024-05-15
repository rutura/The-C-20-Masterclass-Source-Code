#include <fmt/format.h>
#include <list>


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

  std::list<int> numbers = { 11, 12, 13, 14, 15 };

  // Code1 : Element access
  fmt::println("---------------------");
  fmt::println("");
  fmt::println("element access : ");

  print_collection(numbers);

  fmt::println(" front element : {}", numbers.front());
  fmt::println(" back element : {}", numbers.back());


  // Code2 : Iterators : forward and back, and constant
  fmt::println("");
  fmt::println("iterators : ");

  auto it = numbers.begin();

  fmt::print(" (iterators) list of numbers : [");
  while (it != numbers.end()) {
    fmt::print(" {}", *it);
    ++it;
  }
  fmt::println("]");

  // Reverse iterators
  auto it_back = numbers.rbegin();

  fmt::print(" (iterators) list of numbers (reverse) : [");
  while (it_back != numbers.rend()) {
    fmt::print(" {}", *it_back);
    ++it_back;
  }
  fmt::println("]");


  // Code3 : Capacity
  fmt::println("---------------------");

  fmt::println("");
  fmt::println("capacity : ");
  fmt::println(" list max_size : {}", numbers.max_size());
  fmt::println(" list is empty : {}", numbers.empty());
  fmt::println(" list size : {}", numbers.size());


  // Code4 : Modifiers

  fmt::println("---------------------");
  fmt::println("");
  fmt::println("modifiers : ");


  // Clear
  fmt::println("");
  fmt::println("clear :");
  print_collection(numbers);

  numbers.clear();

  print_collection(numbers);
  fmt::println(" numbers is empty : {}", numbers.empty());

  // Insert
  fmt::println("");
  fmt::println("insert : ");
  numbers = { 11, 12, 13, 14, 15 };

  print_collection(numbers);
  auto it_insert = std::find(numbers.begin(), numbers.end(), 13);

  if (it_insert != numbers.end()) numbers.insert(it_insert, 333);// Inserts after it_insert

  print_collection(numbers);


  // Emplace
  fmt::println("");
  fmt::println("emplace : ");

  print_collection(numbers);

  it_insert = std::find(numbers.begin(), numbers.end(), 14);// Emplace in front of 14

  if (it_insert != numbers.end()) numbers.emplace(it_insert, 444);

  print_collection(numbers);


  // Erase
  fmt::println("");
  fmt::println("erase : ");

  print_collection(numbers);

  auto it_erase = std::find(numbers.begin(), numbers.end(), 333);

  if (it_erase != numbers.end()) {
    fmt::println("Found 333 !");
  } else {
    fmt::println("Couldn't find 333 !");
  }

  // Erase the 333
  if (it_erase != numbers.end()) numbers.erase(it_erase);

  print_collection(numbers);


  // Pop_front and pop_back
  // pop_front
  fmt::println("");
  fmt::println("pop_front : ");

  print_collection(numbers);

  numbers.pop_front();

  print_collection(numbers);

  // pop_back
  fmt::println("");
  fmt::println("pop_back : ");

  print_collection(numbers);

  numbers.pop_back();

  print_collection(numbers);


  // Push front and push_back
  // push_front
  fmt::println("");
  fmt::println("push_front : ");

  print_collection(numbers);

  numbers.push_front(111);

  print_collection(numbers);

  // push_back
  fmt::println("");
  fmt::println("push_back : ");

  print_collection(numbers);

  numbers.push_back(222);

  print_collection(numbers);


  // emplace front and back
  fmt::println("");
  fmt::println("emplace front (333) and back (444) : ");

  print_collection(numbers);

  numbers.emplace_front(333);
  numbers.emplace_back(444);

  print_collection(numbers);


  // resize : up or down
  fmt::println("");
  fmt::println("resize : ");

  print_collection(numbers);
  fmt::println(" numbers size : {}", numbers.size());

  numbers.resize(20);

  print_collection(numbers);
  fmt::println(" numbers size : {}", numbers.size());

  numbers.resize(3);// When you resize down, the elements are lost for good.
                    // if you resize up again,you won't get them back.

  print_collection(numbers);
  fmt::println(" numbers size : {}", numbers.size());

  numbers.resize(20);

  print_collection(numbers);
  fmt::println(" numbers size : {}", numbers.size());


  // swap
  fmt::println("");
  fmt::println("swap : ");

  std::list<int> other_numbers{ 200, 400, 600 };

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
  fmt::println("---------------------");
  fmt::println("Other operations : ");

  // Merge
  fmt::println("");
  fmt::println("merge : ");

  std::list<int> numbers1{ 1, 5, 6 };
  std::list<int> numbers2{ 9, 2, 4 };

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


  // splice : move elements from one collection to another
  //           numbers2 is moved into numbers1
  fmt::println("");
  fmt::println("splice : ");

  numbers1 = { 1, 5, 6, 8, 3 };
  numbers2 = { 9, 2, 4, 7, 13, 11, 17 };

  fmt::print(" numbers1 : ");
  print_collection(numbers1);
  fmt::print(" numbers2 : ");
  print_collection(numbers2);

  // Find the iterator you want to start splicing from
  auto it_splice = std::find(numbers1.begin(), numbers1.end(), 6);

  if (it_splice != numbers1.end()) numbers1.splice(it_splice, numbers2);

  fmt::print(" numbers1 : ");
  print_collection(numbers1);
  fmt::print(" numbers2 : ");
  print_collection(numbers2);


  // Remove
  fmt::println("");
  fmt::println("remove : ");

  numbers = { 1, 100, 2, 3, 10, 1, 11, -1, 12 };

  print_collection(numbers);

  numbers.remove(1);// remove both elements equal to 1

  print_collection(numbers);

  // Remove predicate: Can be a function pointer, functor or lambda function.
  //  Will explore this in more details later in the chapter when we talk about algorithms.
  numbers.remove_if([](int n) { return n > 10; });

  print_collection(numbers);


  // reverse
  fmt::println("");
  fmt::println("reverse : ");

  numbers = { 1, 100, 2, 3, 10, 1, 11, -1, 12 };

  print_collection(numbers);

  numbers.reverse();

  print_collection(numbers);


  // Unique : Remove contiguous duplicates
  fmt::println("");
  fmt::println("unique : ");

  numbers = { 1, 100, 100, 2, 3, 10, 1, 11, 11, -1, 12, 10, 1 };

  print_collection(numbers);

  numbers.unique();

  print_collection(numbers);


  // Sort
  fmt::println("");
  fmt::println("sort : ");

  print_collection(numbers);

  numbers.sort();

  print_collection(numbers);

  numbers.unique();

  print_collection(numbers);

  return 0;
}