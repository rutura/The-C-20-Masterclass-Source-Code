/*
    . An example of how full specializations can be used to build our own type trait.
*/
module;

export module templates_5;

namespace templates_5{

    // Primary template (default case: type is not int)
    export template <typename T>
    struct is_int {
        constexpr static  bool value = false;
    };

    // Specialization for int
    template <>
    struct is_int<int> {
        constexpr static bool value = true;
    };
    
} // namespace templates_5