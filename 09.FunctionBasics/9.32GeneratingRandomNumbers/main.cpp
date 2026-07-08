#include <print>
#include <random>

int main() {

    // std::random_device seeds the generator with actual entropy from the
    // OS, so the sequence differs on every run - the modern replacement
    // for the old std::srand(std::time(0)) seeding trick.
    std::random_device rd;

    // The engine itself, seeded once. mt19937 (Mersenne Twister) is the
    // standard library's general-purpose choice.
    std::mt19937 gen(rd());

    /*
    // A distribution shapes the engine's raw output into a specific range.
    // uniform_int_distribution gives every value in [1, RAND_MAX-equivalent]
    // an equal chance - here every int the engine can produce.
    std::uniform_int_distribution<int> full_range_dist;
    int random_num = full_range_dist(gen);
    std::println("random_num : {}", random_num); // full engine range

    random_num = full_range_dist(gen);
    std::println("random_num : {}", random_num);
    */

    // Generate random numbers in a loop
    /*
    std::uniform_int_distribution<int> full_range_dist;
    for (size_t i{0}; i < 20; ++i) {
        std::println("random_num {} : {}", i, full_range_dist(gen));
    }
    */

    // Generate a range between 0 and 10 - the distribution itself takes
    // the bounds, no more error-prone % arithmetic needed.
    /*
    std::uniform_int_distribution<int> dist(0, 10);
    for (size_t i{0}; i < 20; ++i) {
        std::println("random_num {} : {}", i, dist(gen));
    }
    */

    // [1~10]
    std::uniform_int_distribution<int> dist(1, 10);
    for (size_t i{0}; i < 20; ++i) {
        std::println("random_num {} : {}", i, dist(gen));
    }

    return 0;
}
