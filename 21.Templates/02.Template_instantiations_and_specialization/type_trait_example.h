#pragma once

namespace type_trait_example {
// Primary template (default case: type is not int)
export template<typename T> struct is_int
{
  constexpr static bool value = false;
};

// Specialization for int
template<> struct is_int<int>
{
  constexpr static bool value = true;
};

}// namespace type_trait_example