#include <print>

int add_numbers(int first, int second) {
    int result{first + second};
    return result;
}

int main() {

    int first_number{13};
    int second_number{7};

    std::println("First number: {}", first_number);
    std::println("Second number: {}", second_number);

    int sum{first_number + second_number};
    std::println("Sum: {}", sum);

    sum = add_numbers(25, 7);
    std::println("Sum: {}", sum);

    // A function call can be used directly wherever a value is expected.
    std::println("Sum: {}", add_numbers(3, 42));

    return 0;
}
