module;

#include <concepts>

export module concepts_05;

namespace concepts_05{

    // This syntax constrains the auto parameters you pass in
    // to comply with the std::integral concept
    export std::integral auto add(std::integral auto a, std::integral auto b) { return a + b; }

}   // namespace concepts_05