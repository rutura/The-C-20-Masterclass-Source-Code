#pragma once

#include "boxcontainer.h"

#include <string>
#include <iostream>

namespace function_pointers_02 {

char encrypt(const char &param);

char decrypt(const char &param)
{
  // Callback function
  return static_cast<char>(param - 3);
}


std::string &modify(std::string &str_param, char (*modifier)(const char &));


// Modifying a BoxContainer of strings
box::BoxContainer<std::string> &modify(box::BoxContainer<std::string> &sentence, char (*modifier)(const char &));


std::string get_best(const box::BoxContainer<std::string> &sentence,
  bool (*comparator)(const std::string &str1, const std::string &str2));


bool larger_in_size(const std::string &str1, const std::string &str2);

bool greater_lexicographically(const std::string &str1, const std::string &str2);

//Function pointer type aliases.
// Using syntax
using str_comparator = bool (*)(const std::string &str1, const std::string &str2);

//With typedefs
// typedef bool(*str_comparator) (const std::string& str1, const std::string& str2);

}