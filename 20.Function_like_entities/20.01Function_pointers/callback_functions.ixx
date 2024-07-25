module;

#include <string>
#include <vector>

export module callback_functions;

namespace callback_functions{

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
    /*
    BoxContainer<std::string> &modify(BoxContainer<std::string> &sentence, char (*modifier)(const char &))
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
    */

    export std::vector<std::string>& modify(std::vector<std::string>& sentence, char (*modifier)(const char&))
    {
        for (size_t i{}; i < sentence.size(); ++i) {
            // Loop through the word modifying each character
            for (size_t j{}; j < sentence[i].size(); ++j) {
                sentence[i][j] = modifier(sentence[i][j]);
            }
        }
        return sentence;
    }


    /*
    std::string get_best(const BoxContainer<std::string> &sentence,
                        bool (*comparator)(const std::string &str1, const std::string &str2))
    {

    std::string best = sentence.get_item(0);
    for (size_t i{}; i < sentence.size(); ++i) {

        if (comparator(sentence.get_item(i), best)) { best = sentence.get_item(i); }
    }

    return best;
    }
    */
    export std::string get_best(const std::vector<std::string>& sentence,
                        bool (*comparator)(const std::string& str1, const std::string& str2))
    {
        std::string best = sentence[0];
        for (size_t i = 1; i < sentence.size(); ++i) {
            if (comparator(sentence[i], best)) {
                best = sentence[i];
            }
        }
        return best;
    }


    export bool larger_in_size(const std::string &str1, const std::string &str2)
    {
    if (str1.size() > str2.size())
        return true;
    else
        return false;
    }

    export bool greater_lexicographically(const std::string &str1, const std::string &str2) { return (str1 > str2); }

    //Type aliases: Remember to export
    //Using syntax
    export using str_comparator = bool (*)(const std::string &str1, const std::string &str2);

    //With typedefs
    //export typedef bool(*str_comparator) (const std::string& str1, const std::string& str2);

}   //namespace callback_functions