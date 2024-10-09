/*
    . Exploring the basic syntax of C++20 Concepts.
*/
module;

#include <concepts>

export module concepts_01;

namespace concepts_01 {
    // Syntax1
    /*
    export template <typename T>
    requires std::integral<T>
    T add(T a, T b) {
        return a + b;
    }
    */

    // Syntax2
    /*
    export template <std::integral T>
    T add(T a, T b) {
        return a + b;
    }
    */

    // Syntax3
    /*
    export auto add(std::integral auto a, std::integral auto b) {
        return a + b;
    }
    */

    // Syntax4
    export template <typename T>
    T add(T a, T b) requires std::integral<T> {
        return a + b;
    }

    export template <typename T>
    T add(T a, T b) {
        return a + b;
    }

} // namespace concepts_01