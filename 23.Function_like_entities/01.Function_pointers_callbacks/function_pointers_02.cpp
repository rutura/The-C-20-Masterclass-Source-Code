#include "function_pointers_02.h"

namespace function_pointers_02 {
char encrypt(const char &param)
{
  // Callback function
  return static_cast<char>(param + 3);
}

std::string &modify(std::string &str_param, char (*modifier)(const char &))
{
  for (size_t i{}; i < str_param.size(); ++i) {
    str_param[i] = modifier(str_param[i]);// Calling the callback
  }
  return str_param;
}

box::BoxContainer<std::string> &modify(box::BoxContainer<std::string> &sentence, char (*modifier)(const char &))
{
  for (size_t i{}; i < sentence.size(); ++i) {

    // Code below relies on get_item() to return a reference
    // Loop through the word modifying each character
    for (size_t j{}; j < sentence.get_item(i).size(); ++j) {
      sentence.get_item(i)[j] = modifier(sentence.get_item(i)[j]);
    }
  }
  return sentence;
}

std::string get_best(const box::BoxContainer<std::string> &sentence,
  bool (*comparator)(const std::string &str1, const std::string &str2))
{

  std::string best = sentence.get_item(0);
  for (size_t i{}; i < sentence.size(); ++i) {
    if (comparator(sentence.get_item(i), best)) { best = sentence.get_item(i); }
  }

  return best;
}


bool larger_in_size(const std::string &str1, const std::string &str2)
{
  if (str1.size() > str2.size()) return true;
  else return false;
}

bool greater_lexicographically(const std::string &str1, const std::string &str2) { return (str1 > str2); }

}