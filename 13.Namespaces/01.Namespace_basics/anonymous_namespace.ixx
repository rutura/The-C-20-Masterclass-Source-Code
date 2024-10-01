module;

export module anonymous_namespace;

namespace {
    //Subtract can't be exported and used in external modules because it is constrained
    // to the current translation unit.
    /*
    export double subtract(double a, double b)
    {// Only usable in this translation unit
        return a - b;
    }
    */
}// namespace