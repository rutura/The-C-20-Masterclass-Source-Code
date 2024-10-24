/*
    .#2: Callback functions: 
*/
module;

#include <string>
#include <iostream>

export module function_pointers_02;

import box_container_it_5;

using iteration_5::BoxContainer; 

    
namespace function_pointers_02{

    export char encrypt(const char &param)
    {// Callback function
        return static_cast<char>(param + 3);
    }

    export char decrypt(const char &param)
    {// Callback function
        return static_cast<char>(param - 3);
    }


    export std::string &modify(std::string &str_param, char (*modifier)(const char &))
    {
        for (size_t i{}; i < str_param.size(); ++i) {
            str_param[i] = modifier(str_param[i]);// Calling the callback
        }
        return str_param;
    }

    // Modifying a BoxContainer of strings
    export BoxContainer<std::string> &modify(BoxContainer<std::string> &sentence, char (*modifier)(const char &))
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


    export std::string get_best(const BoxContainer<std::string> &sentence,
    bool (*comparator)(const std::string &str1, const std::string &str2))
    {

        std::string best = sentence.get_item(0);
        for (size_t i{}; i < sentence.size(); ++i) {

            if (comparator(sentence.get_item(i), best)) { best = sentence.get_item(i); }
        }

        return best;
    }


    export bool larger_in_size(const std::string &str1, const std::string &str2) {
        return str1.size() > str2.size();
    }

    export bool greater_lexicographically(const std::string &str1, const std::string &str2) { return (str1 > str2); }

    //Function pointer type aliases.
    // Using syntax
    export using str_comparator = bool (*)(const std::string &str1, const std::string &str2);

    //With typedefs
    //export typedef bool(*str_comparator) (const std::string& str1, const std::string& str2);

}