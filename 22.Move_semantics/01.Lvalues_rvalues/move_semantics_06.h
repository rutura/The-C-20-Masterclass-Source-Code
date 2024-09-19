/*
    This file contains code that demonstrates how to invalidate pointers after std::move'ing.
*/

#pragma once
#include "boxcontainer.h"

namespace move_semantics_06 {

inline void populate_box(box::BoxContainer<int> &box, int modifier)
{
  for (size_t i{ 0 }; i < 20; ++i) { box.add((i + 1) * modifier); }
}

}// namespace move_semantics_06