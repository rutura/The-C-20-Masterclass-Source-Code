/*
    This file contains code that explores the stream iterators.
    Input stream iterators and output stream iterators are used to read from and write to streams.
*/
#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

namespace iterator_adaptors_03 {

//Read data from input until the end of stream is reached.
//End of stream is reached when the user presses Ctrl+D on Unix or Ctrl+Z on Windows.

inline void read_and_print()
{

  // Read integers from std::cin using istream_iterator
  std::istream_iterator<int> inputIter(std::cin);
  std::istream_iterator<int> endIter;// Default constructed end iterator

  //Use a vector constructor that takes two iterators to initialize the vector
  std::vector<int> numbers(inputIter, endIter);// Initialize vector with input

  // Output the integers using ostream_iterator
  std::ostream_iterator<int> outputIter(std::cout, " ");

  std::cout << "You entered: ";
  std::copy(numbers.begin(), numbers.end(), outputIter);// Copy elements to cout

  std::cout << "\n";
}

//Create a functoin that sums up integers between a begining iterator and an end iterator.
//The function should return the sum.
template<typename InputIt> auto sum_up(InputIt begin, InputIt end)
{
  auto sum{ *begin };
  for (auto iter = ++begin; iter != end; ++iter) { sum += *iter; }
  return sum;
}


//Function to read fron cin, sum up and print the sum.
inline void read_sum_print()
{
  // Read integers from std::cin using istream_iterator
  std::istream_iterator<int> inputIter(std::cin);
  std::istream_iterator<int> endIter;// Default constructed end iterator

  auto result = sum_up(inputIter, endIter);
  std::cout << "The sum is: " << result << "\n";
}


}// namespace iterator_adaptors_03