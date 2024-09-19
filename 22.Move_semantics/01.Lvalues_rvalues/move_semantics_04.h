/*
    This file contains code that demonstrates move constructor and move assignment operator.
*/
#pragma once
#include "boxcontainer.h"

namespace move_semantics_04 {

inline void populate_box(box::BoxContainer<int> &box, int modifier)
{
  for (size_t i{ 0 }; i < 20; ++i) { box.add((i + 1) * modifier); }
}

inline box::BoxContainer<int> make_box(int modifier)
{
  box::BoxContainer<int> local_int_box(20);
  populate_box(local_int_box, modifier);
  return local_int_box;
}

}// namespace move_semantics_04