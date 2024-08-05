module;

#include <concepts>

export module class_templates_concepts_04;

namespace class_templates_concepts_04{

    export template <typename T>
    concept Number = (std::integral<T> || std::floating_point<T>) 
                    && !std::same_as<T, bool>
                    && !std::same_as<T, char>;


    export template <Number T, Number  U>
    auto add ( T a, U b){
        return a + b;
    }


}   // namespace class_templates_concepts_04