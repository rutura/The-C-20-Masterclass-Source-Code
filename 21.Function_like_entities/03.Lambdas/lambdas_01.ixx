module;

#include <string>

export module lambdas_01;

import boxcontainer;

namespace lambdas_01{

    export std::string &modify(std::string &str_param, char (*modifier)(const char &))
    {
    for (size_t i{}; i < str_param.size(); ++i) {
        str_param[i] = modifier(str_param[i]);// Calling the callback
    }
    return str_param;
    }


    // Modifying a BoxContainer of strings
    export box::BoxContainer<std::string> &modify(box::BoxContainer<std::string> &sentence, char (*modifier)(const char &))
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


    export std::string get_best(const box::BoxContainer<std::string> &sentence,
    bool (*comparator)(const std::string &str1, const std::string &str2))
    {

    std::string best = sentence.get_item(0);
    for (size_t i{}; i < sentence.size(); ++i) {

        if (comparator(sentence.get_item(i), best)) { best = sentence.get_item(i); }
    }

    return best;
    }

}   // namespace lambdas_01