module;

export module variable_templates;

namespace variable_templates{

    //Using function templates. This feels like a hack.
    export template <typename T>
    constexpr T pi() {
        return T(3.1415926535897932385);
    }

    // Variable template to define Pi for different types
    export template <typename T>
    constexpr T PI = T(3.1415926535897932385);

}   // namespace variable_templates