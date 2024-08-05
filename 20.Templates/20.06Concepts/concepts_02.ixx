module;

#include <concepts>
#include <type_traits>

export module concepts_02;

namespace concepts_02{

    // Syntax1
    /*
    export template <typename T>
    concept MyIntegral = std::is_integral_v<T>;

    MyIntegral auto add( MyIntegral auto a, MyIntegral auto b) {
        return a + b;
    }
    */


    export template<typename T> concept Multipliable = requires(T a, T b)
    {
    a *b;// Just makes sure the syntax is valid
    };


    export template<typename T> concept Incrementable = requires(T a)
    {
    a += 1;
    ++a;
    a++;
    };

    export template<typename T> requires Incrementable<T> T add(T a, T b) { return a + b; }

}   // namespace concepts_02