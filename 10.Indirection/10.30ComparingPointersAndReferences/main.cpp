#include <print>

int main() {

    double double_value{12.34};
    double& ref_double_value{double_value}; // reference to double_value
    double* p_double_value{&double_value};  // pointer to double_value

    std::println("double_value : {}", double_value);
    std::println("ref_double_value : {}", ref_double_value);
    std::println("p_double_value : {}", static_cast<const void*>(p_double_value));
    std::println("*p_double_value : {}", *p_double_value);

    // Writing through the pointer
    *p_double_value = 15.44;

    std::println("");
    std::println("double_value : {}", double_value);
    std::println("ref_double_value : {}", ref_double_value);
    std::println("p_double_value : {}", static_cast<const void*>(p_double_value));
    std::println("*p_double_value : {}", *p_double_value);

    // Writing through the reference
    ref_double_value = 18.44;

    std::println("");
    std::println("double_value : {}", double_value);
    std::println("ref_double_value : {}", ref_double_value);
    std::println("p_double_value : {}", static_cast<const void*>(p_double_value));
    std::println("*p_double_value : {}", *p_double_value);

    double some_other_double{78.45};

    // This does NOT make ref_double_value reference some_other_double - a
    // reference is bound for life. This just assigns some_other_double's
    // *value* into double_value, through the reference - exactly like
    // *p_double_value = ... does through a pointer.
    ref_double_value = some_other_double;

    std::println("Assigning through the reference copies a value in - it doesn't rebind it...");
    std::println("");
    std::println("double_value : {}", double_value);
    std::println("ref_double_value : {}", ref_double_value);
    std::println("p_double_value : {}", static_cast<const void*>(p_double_value));
    std::println("*p_double_value : {}", *p_double_value);

    // A pointer, by contrast, really can be repointed to a different address.
    p_double_value = &some_other_double;
    std::println("Making the pointer point somewhere else...");
    std::println("");
    std::println("double_value : {}", double_value);
    std::println("ref_double_value : {}", ref_double_value);
    std::println("&double_value : {}", static_cast<const void*>(&double_value));
    std::println("&ref_double_value : {}", static_cast<const void*>(&ref_double_value));
    std::println("p_double_value : {}", static_cast<const void*>(p_double_value));
    std::println("*p_double_value : {}", *p_double_value);

    *p_double_value = 555.5;

    std::println("");
    std::println("double_value : {}", double_value);
    std::println("ref_double_value : {}", ref_double_value);
    std::println("&double_value : {}", static_cast<const void*>(&double_value));
    std::println("&ref_double_value : {}", static_cast<const void*>(&ref_double_value));
    std::println("p_double_value : {}", static_cast<const void*>(p_double_value));
    std::println("*p_double_value : {}", *p_double_value);

    return 0;
}
