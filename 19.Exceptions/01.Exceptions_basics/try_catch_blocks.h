#pragma once

#include <fmt/format.h>


namespace try_catch_blocks {

class Item
{
public:
  Item() { fmt::println("Item constructor called"); }

  ~Item() { fmt::println("Item destructor called"); }
};

class MyException
{
public:
  MyException() = default;

  // MyException(const MyException & ex) = delete;
public:
  MyException(const MyException &ex) {}
};

}// namespace try_catch_blocks