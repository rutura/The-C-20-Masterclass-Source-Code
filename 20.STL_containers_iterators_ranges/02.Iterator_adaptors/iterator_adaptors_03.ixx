/*
    . Exploring stream iteators
        . Using istream_iterator to read from std::cin
        . Using ostream_iterator to write to std::cout
        . These facilities work really well with the standard algorithms
*/
module;

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

export module iterator_adaptors_03;

namespace iterator_adaptors_03{

    //Read data from input until the end of stream is reached.
    //End of stream is reached when the user presses Ctrl+D on Unix or Ctrl+Z on Windows.

    export void read_and_print(){

        // Read integers from std::cin using istream_iterator
        std::istream_iterator<int> inputIter(std::cin);
        std::istream_iterator<int> endIter; // Default constructed end iterator

        //Use a vector constructor that takes two iterators to initialize the vector
        std::vector<int> numbers(inputIter, endIter); // Initialize vector with input

        // Output the integers using ostream_iterator
        std::ostream_iterator<int> outputIter(std::cout, " ");

        std::cout << "You entered: ";
        std::copy(numbers.begin(), numbers.end(), outputIter); // Copy elements to cout

        std::cout << "\n";
    }

    //A function that sums up the elements in a range: [begin, end)
    template <typename InputIt>
    auto sum_up(InputIt begin, InputIt end){
        auto sum {*begin};
        for(auto iter = ++begin; iter != end; ++iter){
            sum += *iter;
        }
        return sum;
    }


    //Function to read fron cin, sum up and print the sum.
    export void read_sum_print(){
        // Read integers from std::cin using istream_iterator
        std::istream_iterator<int> inputIter(std::cin);
        std::istream_iterator<int> endIter; // Default constructed end iterator

        auto result = sum_up(inputIter, endIter);
        std::cout << "The sum is: " << result << "\n";
    }

    
}   // namespace iterator_adaptors_03