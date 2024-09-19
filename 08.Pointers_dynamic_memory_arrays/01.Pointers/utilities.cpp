#include "utilities.h"

#include "pointers_and_arrays.h"
#include "pointers_and_const.h"
#include "pointer_arithmetic.h"
#include "pointer_basics.h"

#include <string_view>
#include <fmt/format.h>

void pointer_basics_demo() { pointer_basics::tinker_with_pointers(); }

void pointer_and_const_demo() { pointers_and_const::const_pointer_and_pointer_to_const(); }

void pointers_and_arrays_demo()
{
  //pointers_and_arrays::tinker_with_pointers_and_arrays();
  pointers_and_arrays::swap_addresses();
}

void pointer_arithmetic_demo()
{
  //pointer_arithmetic::p_a_navigation();
  pointer_arithmetic::p_a_distance();
}