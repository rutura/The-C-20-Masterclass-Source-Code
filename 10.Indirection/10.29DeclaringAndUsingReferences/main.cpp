#include <print>

int main() {

    int int_data{33};
    double double_data{55};

    // A reference is bound to its target for its whole lifetime - it's
    // never a separate object, just another name for int_data/double_data.
    int& ref_int_data{int_data};
    double& ref_double_data{double_data};

    std::println("int_data : {}", int_data);
    std::println("&int_data : {}", static_cast<const void*>(&int_data));
    std::println("double_data : {}", double_data);
    std::println("&double_data : {}", static_cast<const void*>(&double_data));

    std::println("=======================");

    std::println("ref_int_data : {}", ref_int_data);
    std::println("&ref_int_data : {}", static_cast<const void*>(&ref_int_data));
    std::println("ref_double_data : {}", ref_double_data);
    std::println("&ref_double_data : {}", static_cast<const void*>(&ref_double_data));

    int_data = 111;
    double_data = 67.2;

    std::println("");
    std::println("int_data : {}", int_data);
    std::println("&int_data : {}", static_cast<const void*>(&int_data));
    std::println("double_data : {}", double_data);
    std::println("&double_data : {}", static_cast<const void*>(&double_data));

    std::println("=======================");

    // The reference and its target always show the same value and the
    // same address - there's no way to tell them apart from the outside.
    std::println("ref_int_data : {}", ref_int_data);
    std::println("&ref_int_data : {}", static_cast<const void*>(&ref_int_data));
    std::println("ref_double_data : {}", ref_double_data);
    std::println("&ref_double_data : {}", static_cast<const void*>(&ref_double_data));

    ref_int_data = 1012;
    ref_double_data = 1000.45;

    std::println("");
    std::println("int_data : {}", int_data);
    std::println("&int_data : {}", static_cast<const void*>(&int_data));
    std::println("double_data : {}", double_data);
    std::println("&double_data : {}", static_cast<const void*>(&double_data));

    std::println("=======================");

    std::println("ref_int_data : {}", ref_int_data);
    std::println("&ref_int_data : {}", static_cast<const void*>(&ref_int_data));
    std::println("ref_double_data : {}", ref_double_data);
    std::println("&ref_double_data : {}", static_cast<const void*>(&ref_double_data));

    return 0;
}
