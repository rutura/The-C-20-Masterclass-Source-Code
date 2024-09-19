/*
    This file contains code that demonstrates passing by rvalue reference.
*/
#pragma once

#include <iostream>


namespace move_semantics_08 {


class Item
{
  friend std::ostream &operator<<(std::ostream &out, const Item &operand);

public :
  Item()
    : m_data{ new int } {}

  Item(int value)
    : m_data{ new int(value) } {}

  //Copy Members
  Item(const Item &source)
    : m_data{ new int }
  {
    std::cout << "Item copy constructor copying data..." << "\n";
    *m_data = (*source.m_data);
  }

  Item &operator=(const Item &right_operand)
  {
    std::cout << "Item copy assignment operator copying data..." << "\n";
    if (&right_operand != this) { *m_data = (*right_operand.m_data); }
    return *this;
  }

  //Move Members
  Item(Item &&source)
  {
    std::cout << "Item move constructor moving data..." << "\n";
    //Steal the pointer
    m_data = source.m_data;

    //Reset the source pointer
    source.m_data = nullptr;
  }

  Item &operator=(Item &&right_operand)
  {
    std::cout << "Item move assignment operator moving data..." << "\n";
    if (&right_operand != this) {

      //Steal the pointer
      m_data = right_operand.m_data;

      //Reset the source pointer
      right_operand.m_data = nullptr;
    }
    return *this;
  }

private :
  int *m_data{ nullptr };
};


std::ostream &operator<<(std::ostream &out, const Item &operand);


Item get_value();


void do_something(Item &&item);

}// namespace move_semantics_08