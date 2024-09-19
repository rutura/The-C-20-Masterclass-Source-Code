#pragma once
#include "boxcontainer.h"

#include <functional>
#include <string>

namespace std_function {

// Function pointer
inline char encrypt(const char &param) { return static_cast<char>(param + 3); }

// Functor
class Decrypt
{
public:
  char operator()(const char &param) { return static_cast<char>(param - 3); }
};


// Modifying a BoxContainer of strings
inline box::BoxContainer<std::string> &modify(box::BoxContainer<std::string> &sentence,
  // char(*modifier) (const char&)){
  std::function<char(const char &)> modifier)
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

inline std::string get_best(const box::BoxContainer<std::string> &sentence,
  // bool(*comparator)(const std::string& str1, const std::string& str2)){
  std::function<bool(const std::string &str1, const std::string &str2)> comparator)
{

  std::string best = sentence.get_item(0);
  for (size_t i{}; i < sentence.size(); ++i) {
    if (comparator(sentence.get_item(i), best)) { best = sentence.get_item(i); }
  }

  return best;
}

// Function pointer
inline bool larger_in_size(const std::string &str1, const std::string &str2)
{
  if (str1.size() > str2.size()) return true;
  else return false;
}

}// namespace std_function