module;

#include <string>

export module functors_01;

namespace functors_01 {

    // The functors
    export class Encrypt {
    public:
    char operator()(const char &param) { return static_cast<char>(param + 3); }
    };

    export class Decrypt {
    public:
    char operator()(const char &param) { return static_cast<char>(param - 3); }
    };

    // The function pointers
    export char encrypt(const char &param) {  // Callback function
    return static_cast<char>(param + 3);
    }

    export char decrypt(const char &param) {  // Callback function
    return static_cast<char>(param - 3);
    }

    export template <typename Modifier>
    std::string &modify(std::string &str_param, Modifier modifier) {
    for (size_t i{}; i < str_param.size(); ++i) {
        str_param[i] = modifier(str_param[i]);  // Calling the callback
    }
    return str_param;
    }

}  // namespace functors_01