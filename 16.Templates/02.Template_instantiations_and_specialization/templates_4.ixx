/*
    . Exploring template full specialization.
        . Full specialization happens when you provide a complete definition for a specific type or function, completely overriding the generic (original) template.

        . Full specialization takes precedence over the primary(generic) template and any partial specialization.

        . When the compiler a call to a function call or object instantiation, it will first look for a full specialization, then a partial specialization, and finally the primary template.

*/
module;

#include<fmt/format.h>

export module templates_4;

namespace templates_4{

    // Generic (primary) template
    export template <typename T>
    class Adder {
    public:
        T add(T a, T b) {
            fmt::println("Generic template class");
            return a + b;
        }
    };

    // Full specialization for int
    template <>
    class Adder<int> {
    public:
        int add(int a, int b) {
            fmt::println("Specialized template class for int");
            return a + b;
        }
    };

    //Full specialization for const char*
    template <>
    class Adder<const char*> { 
    public:
        char* add(char* a,char* b) {
            fmt::println("Specialized template class for const char*");
            return std::strcat(a, b);
        }
    };

    //Function template specialization
    // Primary template
    export template <typename T>
    T add(T a, T b) {
        fmt::println("Generic template function");
        return a + b;
    } 

    template<>
    char* add<char*>(char* a, char* b) {
        fmt::println("Specialized template function for char*");
        return std::strcat(a, b);
    }

    
} // namespace templates_4