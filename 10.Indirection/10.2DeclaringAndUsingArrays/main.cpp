#include <print>

int main() {

    // Declare an array of ints
    // int scores[10]; // uninitialized - contains junk data

    // Read data
    // std::println("scores[0] : {}", scores[0]);
    // std::println("scores[1] : {}", scores[1]);

    // Read with a loop
    /*
    for (size_t i{0}; i < 10; ++i) {
        std::println("scores[{}] : {}", i, scores[i]);
    }
    */

    /*
    scores[0] = 20;
    scores[1] = 21;
    scores[2] = 22;

    for (size_t i{0}; i < 10; ++i) {
        std::println("scores[{}] : {}", i, scores[i]);
    }
    */

    // Write data in a loop
    /*
    for (size_t i{0}; i < 10; ++i) {
        scores[i] = i * 10;
    }

    for (size_t i{0}; i < 10; ++i) {
        std::println("scores[{}] : {}", i, scores[i]);
    }
    */

    // Declare and initialize at the same time
    /*
    double salaries[5]{12.7, 7.5, 13.2, 8.1, 9.3};

    for (size_t i{0}; i < 5; ++i) {
        std::println("salary[{}] : {}", i, salaries[i]);
    }
    */

    // If you don't initialize all the elements, the rest default to 0
    /*
    int families[5]{12, 7, 5};

    for (size_t i{0}; i < 5; ++i) {
        std::println("families[{}] : {}", i, families[i]);
    }
    */

    // Omit the size at declaration - the compiler counts the initializers
    /*
    int class_sizes[]{10, 12, 15, 11, 18, 17, 23, 56};

    for (auto value : class_sizes) {
        std::println("value : {}", value);
    }
    */

    // Read-only arrays
    /*
    const int birds[]{10, 12, 15, 11, 18, 17, 23, 56};
    birds[2] = 8; // compiler error: birds is const
    */

    // Sum up the scores array
    int scores[]{2, 5, 8, 2, 5, 6, 9};
    int sum{0};

    for (int element : scores) {
        sum += element;
    }
    std::println("Score sum : {}", sum);

    return 0;
}
