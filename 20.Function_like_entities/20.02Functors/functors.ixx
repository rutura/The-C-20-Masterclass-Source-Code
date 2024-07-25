module;

#include <string>

export module functors;

namespace functors{

    //Encrypt functor
    export class Encrypt
    {
    public:
    char operator()(const char &param) { return static_cast<char>(param + 3); }
    };
    

    //Decrypt functor
    export class Decrypt
    {
    public:
    char operator()(const char &param) { return static_cast<char>(param - 3); }
    };

    //Other function like entities
    export char encrypt(const char &param)
    {// Callback function
    return static_cast<char>(param + 3);
    }

    export char decrypt(const char &param)
    {// Callback function
    return static_cast<char>(param - 3);
    }

    //Tease the students that we can use templates to make the modify function more generic
    /*
    export template<typename Modifier> 
    std::string &modify(std::string &str_param, Modifier modifier)
    {
    for (size_t i{}; i < str_param.size(); ++i) {
        str_param[i] = modifier(str_param[i]);// Calling the callback
    }
    return str_param;
    }
    */

    //Write a modify function that uses a function pointer like encrypt and decrypt
    export std::string &modify(std::string &str_param, char (*modifier)(const char &))
    {
    for (size_t i{}; i < str_param.size(); ++i) {
        str_param[i] = modifier(str_param[i]);// Calling the callback
    }
    return str_param;
    }

    //Write a modify function that takes a functor like Encrypt
    export std::string &modify(std::string &str_param, Encrypt modifier)
    {
    for (size_t i{}; i < str_param.size(); ++i) {
        str_param[i] = modifier(str_param[i]);// Calling the callback
    }
    return str_param;
    }

    //Write a modify function that takes a functor like Decrypt
    export std::string &modify(std::string &str_param, Decrypt modifier)
    {
    for (size_t i{}; i < str_param.size(); ++i) {
        str_param[i] = modifier(str_param[i]);// Calling the callback
    }
    return str_param;
    }

}   // namespace functors