#include <print>

// Declaration - a reference to an array of exactly 10 doubles. Unlike a
// plain array parameter, this doesn't decay to a pointer, so the compiler
// enforces the size at the call site instead of trusting a separate count.
double sum(const double (&scores)[10]);

int main() {

    double student_scores[]{10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 1};

    double sum_result = sum(student_scores);
    std::println("result is : {}", sum_result);

    return 0;
}

// Definition
double sum(const double (&scores)[10]) {
    double sum{};
    for (size_t i{}; i < std::size(scores); ++i) {
        sum += scores[i];
    }
    return sum;
}
