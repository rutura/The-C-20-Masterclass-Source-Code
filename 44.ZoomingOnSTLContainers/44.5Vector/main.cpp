#include <fmt/format.h>
#include <vector>


class Item
{
public:
  Item() : m_var(0) { fmt::println("Item default constructor called"); }
  Item(int var) : m_var(var)
  {
    // fmt::println( "Item constructor called for: {}" , m_var );
  }
  Item(int var1, int var2) : m_var(var1 * var2) {}

  Item(const Item &source) : m_var{ source.m_var }
  {
    // fmt::println( "Item copy constructor called for :{}" , m_var );
  }

  int get() const { return m_var; }

private:
  int m_var{ 0 };
};

std::ostream &operator<<(std::ostream &out, const Item &item)
{
  out << "Item [ value : " << item.get() << "]";
  return out;
}

template<> struct fmt::formatter<Item>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Item &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Item [value: {}]", obj.get());
  }
};

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

  // Code1 :Collection creation and element access
  fmt::println("");
  fmt::println("Creating std::vector's : ");
  std::vector<int> numbers{ 1, 2, 3, 4, 5 };// Default initialized vector.
  std::vector<Item> items{ Item(6), Item(7), Item(8), Item(9), Item(10) };

  fmt::print(" numbers  : ");
  print_collection(numbers);
  fmt::print(" items : ");
  print_collection(items);

  // Accessing elements
  fmt::println("");
  fmt::println("Element access : ");
  fmt::println(" numbers[3] : {}", numbers[3]);// No bound check
  fmt::println(" numbers.at(3) : {}", numbers.at(3));// Bound check

  fmt::println(" numbers[30] (Undefined behavior):{}",
    numbers[30]);// No bounds check, undefined behavior, junk value or even crash.
  // fmt::println( " numbers.at(30) (throws expception): {}" , numbers.at(30) );

  fmt::println(" numbers.front() : {}", numbers.front());
  fmt::println(" numbers.back() :{}", numbers.back());

  // Data method
  fmt::println(" numbers[3] (with underlying data array) : {}", (*(numbers.data() + 3)));


  // Code2 : Iterators
  fmt::println("-----------------------");

  fmt::println("");
  fmt::println("Iterators : ");

  // begin() and end()
  auto it = numbers.begin();

  fmt::print(" Vector(With iterators) : [ ");
  while (it != numbers.end()) {
    fmt::print(" {}", *it);
    ++it;
  }
  fmt::println(" ]");

  // Reverse traversal with rbebin and rend
  auto it_reverse = numbers.rbegin();// non const iterator

  fmt::print(" Vector(Reverse traversal with iterators) : [ ");
  while (it_reverse != numbers.rend()) {
    fmt::println(" {}", *it_reverse);
    ++it_reverse;// Increments towards the first element of the array.
  }
  fmt::println(" ]");

  fmt::println("-----------------------");


  // Code3 : Capacity

  fmt::println("");

  fmt::println("capacity : ");
  fmt::print(" numbers : ");
  print_collection(numbers);

  fmt::println(" numbers size : {}", numbers.size());
  fmt::println(" numbers max_size : {}", numbers.max_size());
  fmt::println(" numbers is empty : {}", numbers.empty());
  fmt::println(" numbers capacity : {}", numbers.capacity());

  numbers.push_back(20);
  fmt::print(" numbers (after push_back) : ");
  print_collection(numbers);
  fmt::println(" numbers capacity : {}", numbers.capacity());

  numbers.shrink_to_fit();
  fmt::print(" numbers (after shrink_to_fit) : ");
  print_collection(numbers);
  fmt::println(" numbers capacity : {}", numbers.capacity());

  numbers.reserve(20);
  fmt::print(" numbers(after reserve) : ");
  print_collection(numbers);
  fmt::println(" numbers size : {}", numbers.size());
  fmt::println(" numbers capacity : {}", numbers.capacity());

  fmt::println("-----------------------");


  // Code4 : Modifier methods

  fmt::println("");
  fmt::println("clear : ");
  print_collection(numbers);

  // Clear
  numbers.clear();

  print_collection(numbers);
  fmt::println(" numbers size : {}", numbers.size());
  fmt::println(" numbers capacity : {}", numbers.capacity());

  numbers = { 10, 20, 30, 40, 50, 60 };

  print_collection(numbers);


  // Insert
  // The element you provide as insert()’s second argument is
  // inserted right before the position referred to
  // by the iterator you provide as its first argument

  fmt::println("");
  fmt::println("insert : ");

  fmt::print(" numbers(before insert) : ");
  print_collection(numbers);

  auto it_pos = numbers.begin() + 2;

  fmt::print("*it_pos : {}", *it_pos);

  numbers.insert(it_pos, 300);
  numbers.insert(it_pos, 400);// As we insert new items, it_pos changes the elements it's
                              // pointing to :it is  invalidated. Originaly it was pointing
                              // to 30. It keeps pointing at position 2 but the content at
                              // that position has changed.
  fmt::print(" numbers (after insert 300,400) : ");
  print_collection(numbers);
  fmt::println("*it_pos : {}", *it_pos);


  // Emplace
  fmt::println("");
  fmt::println("emplace : ");
  print_collection(items);

  auto it_item_pos = items.begin() + 2;
  items.emplace(it_item_pos, 45, 10);// The parameters following the iterator
                                     // are passed to a constructor of the type stored in
                                     // the vector.
  print_collection(items);


  // Erase
  fmt::println("");
  fmt::println("erase : ");
  print_collection(items);

  items.erase(items.begin() + 4);

  print_collection(items);

  // Range : visualize
  items.erase(items.begin() + 1, items.begin() + 4);

  print_collection(items);


  // Emplace_back
  fmt::println("");
  fmt::println("emplace_back : ");
  print_collection(items);

  items.emplace_back(10, 10);// equivalent to items.emplace(items.end() , 10,10);
  items.emplace_back(10, 11);
  items.emplace_back(10, 12);

  /*
  //The above is equivalent to the code below.
  items.emplace(items.end() , 10,10);
  items.emplace(items.end() , 10,11);
  items.emplace(items.end() , 10,12);
  */

  print_collection(items);


  // Pop back
  fmt::println("");
  fmt::println("pop_back : ");
  print_collection(items);

  items.pop_back();

  print_collection(items);

  // Resize
  fmt::println("");
  fmt::println("resize (Before) : ");
  print_collection(items);
  fmt::println("items size : {}", items.size());
  fmt::println("items capacity : {}", items.capacity());

  items.resize(11);// Pay attention on the default constructors being called

  print_collection(items);
  fmt::println("after resize : ");
  fmt::println("items size : {}", items.size());
  fmt::println("items capacity : {}", items.capacity());


  // Swap
  fmt::println("");
  fmt::println("swap : ");


  std::vector<Item> other_items = { Item(22), Item(33), Item(44) };

  fmt::print("items : ");
  print_collection(items);

  fmt::print("other_items : ");
  print_collection(other_items);

  // items.swap(other_items);
  other_items.swap(items);

  fmt::println("after swap : ");

  fmt::print("items : ");
  print_collection(items);

  fmt::print("other_items : ");
  print_collection(other_items);


  return 0;
}