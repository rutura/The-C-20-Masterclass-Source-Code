#pragma once

#include <fmt/format.h>

namespace iterator_adaptors_02 {

//Create an Item class a default constructor, copy construtor, copy assignment operator, move constructor and move assignment operator. The methods shouldn't be defaulted and should print simple messages with fmt.
class Item
{
public:
  Item() { fmt::println("Item default constructor\n"); }

  //Copy semantics
  Item(const Item &other) { fmt::println("Item copy constructor\n"); }

  Item &operator=(const Item &other)
  {
    fmt::println("Item copy assignment operator\n");
    return *this;
  }

  //Move semantics
  Item(Item &&other) { fmt::println("Item move constructor\n"); }

  Item &operator=(Item &&other)
  {
    fmt::println("Item move assignment operator\n");
    return *this;
  }
};

}// namespace iterator_adaptors_02