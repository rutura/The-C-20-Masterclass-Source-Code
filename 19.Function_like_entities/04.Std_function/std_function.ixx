/*
    . std::function: 
        . A common interface for function pointers, functors, and lambdas
*/
module;

#include <functional>
#include <string>

export module std_function;

import box_container_it_5;

using iteration_5::BoxContainer;

namespace std_function{

    // Function pointer
    export char encrypt(const char &param) { 
        return static_cast<char>(param + 3); 
    }

    // Functor
    export class Decrypt {
    public:
        char operator()(const char &param) { 
            return static_cast<char>(param - 3); 
        }
    };

    // Modifying a BoxContainer of strings
    export BoxContainer<std::string> &modify(
        BoxContainer<std::string> &sentence, std::function<char(const char &)> modifier) 
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

    export std::string get_best(
        const BoxContainer<std::string> &sentence,
        std::function<bool(const std::string &str1, const std::string &str2)> comparator) 
    {
        std::string best = sentence.get_item(0);
        for (size_t i{}; i < sentence.size(); ++i) {
            if (comparator(sentence.get_item(i), best)) { 
                best = sentence.get_item(i); 
            }
        }
        return best;
    }

    // Function pointer
    export bool larger_in_size(const std::string &str1, const std::string &str2) {
        return str1.size() > str2.size();
    }

}  // namespace std_function 