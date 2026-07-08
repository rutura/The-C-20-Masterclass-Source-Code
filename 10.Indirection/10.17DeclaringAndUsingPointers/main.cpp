#include <print>

int main() {

    // Declare and initialize a pointer
    /*
    int* p_number{};   // initializes to nullptr
    double* p_fractional_number{};

    // Explicitly initialize with nullptr
    int* p_number1{nullptr};
    int* p_fractional_number1{nullptr};

    // Pointers are all the same size, regardless of what they point to
    std::println("sizeof(int) : {}", sizeof(int));       // 4
    std::println("sizeof(double) : {}", sizeof(double));  // 8
    std::println("sizeof(double*) : {}", sizeof(double*));
    std::println("sizeof(int*) : {}", sizeof(int*));

    // It doesn't matter whether the * sits next to the type or the name
    int* p_number2{nullptr};
    int * p_number3{nullptr};
    int *p_number4{nullptr};

    int *p_number5{}, other_int_var{};
    int* p_number6{}, other_int_var6{}; // confusing - other_int_var6 looks
                                         // like it might also be a pointer,
                                         // but the * only applies to the
                                         // first name in the declaration

    // Clearer to just declare them on separate lines
    int *p_number7{};
    int other_int_var7{}; // no room for confusion
    */

    // Pointers store addresses - the address-of operator (&) gets one
    int int_var{43};
    int* p_int{&int_var};

    std::println("Int var : {}", int_var);
    std::println("p_int (Address in memory) : {}", static_cast<const void*>(p_int));

    // A pointer can be reassigned to point somewhere else at any time
    int int_var1{65};
    p_int = &int_var1;
    std::println("p_int (with different address) : {}", static_cast<const void*>(p_int));

    // Pointers of different types can't cross-assign
    int* p_int1{nullptr};
    double double_var{33};
    // p_int1 = &double_var; // compiler error

    // Dereferencing a pointer reads (or writes) the value it points to
    int* p_int2{nullptr};
    int int_data{56};
    p_int2 = &int_data;

    std::println("value : {}", *p_int2);

    return 0;
}
