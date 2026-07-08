#include <print>

void increment(int& value);
void print_out(const int& value);

int main() {

    /*
    int int_var{3};
    increment(int_var);
    print_out(int_var);
    */

    // double_var can't bind directly to increment's int& parameter - int
    // and double are different types, and a reference can't silently
    // convert between them the way a plain copy could. Converting to an
    // int variable first, then passing that, is the way around it.
    double double_var{3.6};
    int data = double_var;

    increment(data);
    print_out(double_var);

    return 0;
}

void increment(int& value) {
    value++;
    std::println("value incremented to : {}", value);
}

void print_out(const int& value) {
    std::println("value : {}", value);
}
