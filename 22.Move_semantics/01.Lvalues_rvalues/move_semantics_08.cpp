#include "move_semantics_08.h"

namespace move_semantics_08 {

std::ostream &operator<<(std::ostream &out, const Item &operand)
{
  out << "Item : [" << (*operand.m_data) << "]";
  return out;
}

Item get_value() { return Item(22); }

void do_something(Item &&item)
{
  std::cout << "Do something move version called..." << "\n";
  //Item internal = item;
  Item internal = std::move(item);
  std::cout << "internal : " << internal << "\n";
}

}