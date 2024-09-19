#include "function_pointers_03.h"

namespace function_pointers_03 {
bool larger_in_size(const std::string &str1, const std::string &str2)
{
  if (str1.size() > str2.size()) return true;
  else return false;
}

bool greater_lexicographically(const std::string &str1, const std::string &str2) { return (str1 > str2); }

bool larger_int(const int &param1, const int &param2) { return param1 > param2; }


}