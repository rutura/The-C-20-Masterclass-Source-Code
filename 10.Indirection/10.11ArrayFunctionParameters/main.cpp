#include <print>

// double sum(double scores[], size_t count); // equivalent - array
// parameters decay to a pointer, so scores[] and *scores mean the same thing
double sum(double* scores, size_t count) {
    double score_sum{};

    for (size_t i{0}; i < count; ++i) {
        score_sum += scores[i];
    }
    return score_sum;
}

int main() {
    double my_scores[]{10.5, 34.3, 4.8, 6.5};

    double result = sum(my_scores, std::size(my_scores));
    std::println("result : {}", result);

    return 0;
}
